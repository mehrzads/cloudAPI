/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <cblas.h>              /* Basic Linear Algebra I/O */
#include <utility>
#include <math.h>              /* Basic Linear Algebra I/O */
#include "mpi.h"
#include "tcpSocket.h"
#include "compression.h"
#include "cloudmessage.pb.h" 
#include "clblas.h"
#include "scalapack.h"
#include "server.h"
using namespace std;
using namespace cloudmessaging;
using namespace google::protobuf;

PointerMessage pointerMessage;
SizeMessage sizeMessage;
TransferMessage transferMessage;
CommonMessage baseMessage;
FunctionCallMessage functionCallMessage;
string message;
string argsMessage;


int getRootFactor( int n ) {
    for( int t = sqrt(n); t > 0; t-- ) {
        if( n % t == 0 ) {
            return t;
        }
    }
    return 1;
}



// Initializing the connection
void intitializeSocket(int portno,  TCPSocket  & tcpSocket){
  tcpSocket.setnThreads(N_TCP_THREADS);
  tcpSocket.serverListen(portno);
}

void handleAllocationMessage(TCPSocket  & tcpSocket, string message){
  sizeMessage.ParseFromString(message);
  void * cloudPtr = malloc(sizeMessage.size());
  pointerMessage.set_messagetype(PointerCommand);
  pointerMessage.set_pointer(reinterpret_cast<int64_t>(cloudPtr));
  pointerMessage.SerializeToString(&message);
  tcpSocket.sendMessage(message);
}

void handleGetMessage(TCPSocket  & tcpSocket, string message){
  transferMessage.ParseFromString(message);
  if (transferMessage.compresskind() == NoCompression)
    tcpSocket.recData(reinterpret_cast<void *>(transferMessage.pointer()),  transferMessage.size());
  else{
    unsigned char * compressedData = static_cast<unsigned char *>(malloc(transferMessage.compressedsize()));
    if (!compressedData) printf("Allocation is NULL\n");	     
    tcpSocket.recData(static_cast<void *>(compressedData),   transferMessage.compressedsize());
    size_t outputSize = static_cast<size_t>(transferMessage.size());
    decompress(compressedData, transferMessage.compressedsize(), reinterpret_cast<unsigned char *>(transferMessage.pointer()), outputSize, (cloudCompressionKind)transferMessage.compresskind());
    free(compressedData);
  }
}

void handleSendMessage(TCPSocket  & tcpSocket, string message){
  transferMessage.ParseFromString(message);
  if (transferMessage.compresskind() == NoCompression)
    tcpSocket.sendData(reinterpret_cast<void *>(transferMessage.pointer()),  transferMessage.size());
  else{
    size_t compressedSize = getMaxLength(transferMessage.size(), (cloudCompressionKind)transferMessage.compresskind());
    unsigned char *compressedData = static_cast<unsigned char *>(malloc(compressedSize));
    if (!compressedData) printf("Allocation is NULL\n");	
    compress(reinterpret_cast<unsigned char *>(transferMessage.pointer()), static_cast<size_t>(transferMessage.size()), compressedData, compressedSize, 1, (cloudCompressionKind)transferMessage.compresskind());
    sizeMessage.set_messagetype(SizeCommand);
    sizeMessage.set_size(compressedSize);
    sizeMessage.SerializeToString(&message);
    tcpSocket.sendMessage(message);
    tcpSocket.sendData(compressedData, compressedSize);
    free(compressedData);
  }
}

void handleFunctionCallMessage(string message, string argsMessage, MPIInfo mpiInfo){
  functionCallMessage.ParseFromString(message);
  switch (functionCallMessage.functiontype()){
    case ClBlasStart ... ClBlasEnd:
      handleClblasFunction(static_cast<cloudFunctionKind>(functionCallMessage.functiontype()), argsMessage, mpiInfo);
      break;
    default:
      assert("Wrong function call type" && 0);
      break;
  }
}

void handleCloseMessage(TCPSocket  & tcpSocket){
  tcpSocket.closeSocket();
}


void handleFreeMessage(string message){
  pointerMessage.ParseFromString(message);
  free(reinterpret_cast<void *>(pointerMessage.pointer()));
}


void MPIInitialize(MPIInfo & info){
  blacs_pinfo( &info.rank, &info.nProcs );


  info.nRows = getRootFactor(info.nProcs);
  info.nCols = info.nProcs / info.nRows;

  int system = blacs_get( -1, 0 );
  info.grid = blacs_gridinit( system, true, info.nRows, info.nCols );

  blacs_gridinfo( info.grid, info.nRows, info.nCols, &info.myRow, &info.myCol );

  if( info.myRow >= info.nRows || info.myCol >= info.nCols ) {
      blacs_gridexit( info.grid );
      blacs_exit(0);
      exit(0);
  }
}

void MPIClose(MPIInfo info){
  blacs_gridexit(info.grid );
  blacs_exit(0);
}

void broadcastString(bool root, std::string& strg) {
  if (root) {
    int length = strg.size();
    MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);
    char* cstr = const_cast<char*>(strg.c_str());
    MPI_Bcast(cstr, strg.size(), MPI_CHAR, 0, MPI_COMM_WORLD);
  }
  else {
    int length;
    MPI_Bcast(&length, 1, MPI_INT, 0, MPI_COMM_WORLD);
    char* charstr = new char[length+1];
    MPI_Bcast(charstr, length, MPI_CHAR, 0, MPI_COMM_WORLD);
    strg = string(charstr, length);
    delete [] charstr;
  }

  return;
}

void monitor(int portno){
  MPIInfo mpiInfo;
  MPIInitialize(mpiInfo);
  TCPSocket socket;
  int commandKind;
  bool rootProc = (mpiInfo.rank == 0);
  
  if (rootProc) intitializeSocket(portno, socket);
    bool listen = true;
    while(listen){
      if (rootProc){
        socket.recMessage(message);
        baseMessage.ParseFromString(message);	
        commandKind = baseMessage.messagetype();
      }
      MPI_Bcast(&commandKind, 1, MPI_INT, 0, MPI_COMM_WORLD);
      switch(commandKind){
        // Allocating in the memory
        case AllocCommand:
          if (rootProc) handleAllocationMessage(socket, message);
          break;
        // Recieving the data from the client  
        case GetCommand:
          if (rootProc) handleGetMessage(socket, message);
          break;
        // Sending data to the client  
        case SendCommand:
          if (rootProc) handleSendMessage(socket, message);
          break;
        case FunctionCallCommand:
          if (rootProc) socket.recMessage(argsMessage);
          broadcastString(rootProc, message);
          broadcastString(rootProc, argsMessage);
          handleFunctionCallMessage(message, argsMessage, mpiInfo);
          break;
        // Freeing the memory
        case FreeCommand:
          if (rootProc) handleFreeMessage(message);
          break;
        // Closing the connection  
        case CloseCommand:
          if (rootProc) handleCloseMessage(socket);
          listen = false;
          MPIClose(mpiInfo);
          break;
      }
    }

}



int main(int argc, char *argv[])
{
  if (argc < 2) {
      fprintf(stderr,"ERROR, no port provided\n");
      exit(1);
  }
  int portno = atoi(argv[1]);
  monitor(portno);
  return 0; 
}
