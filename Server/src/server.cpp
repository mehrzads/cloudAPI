/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <cblas.h>              /* Basic Linear Algebra I/O */
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <chrono>
#include <utility>
#include <math.h>              /* Basic Linear Algebra I/O */
#include "mpi.h"
#include "common.h"
#include "compression.h"
#include "cloudmessage.pb.h" 
#include "cloudTransfer.h"
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

void error(const char *msg)
{
    perror(msg);
    exit(1);
}


// Initializing the connection
int intitializeSocket(int portno, int &sockfd){

    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, reinterpret_cast<struct sockaddr *>(&serv_addr),
             sizeof(serv_addr)) < 0) 
             error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    int newsockfd = accept(sockfd, 
                reinterpret_cast<struct sockaddr *>(&cli_addr), 
                &clilen);
    if (newsockfd < 0) error("ERROR on accept");
    return newsockfd;
    
}

void handleAllocationMessage(int socketID, string message){
  sizeMessage.ParseFromString(message);
  void * cloudPtr = malloc(sizeMessage.size());
  pointerMessage.set_messagetype(PointerCommand);
  pointerMessage.set_pointer(reinterpret_cast<int64_t>(cloudPtr));
  pointerMessage.SerializeToString(&message);
  sendMessage(socketID, message);
}

void handleGetMessage(int socketID, string message){
  transferMessage.ParseFromString(message);
  if (transferMessage.compresskind() == NoCompression)
    recData(socketID, reinterpret_cast<void *>(transferMessage.pointer()),  transferMessage.size());
  else{
    unsigned char * compressedData = static_cast<unsigned char *>(malloc(transferMessage.compressedsize()));
    if (!compressedData) printf("Allocation is NULL\n");	     
    recData(socketID, static_cast<void *>(compressedData),   transferMessage.compressedsize());
    size_t outputSize = static_cast<size_t>(transferMessage.size());
    decompress(compressedData, transferMessage.compressedsize(), reinterpret_cast<unsigned char *>(transferMessage.pointer()), outputSize, (cloudCompressionKind)transferMessage.compresskind());
    free(compressedData);
  }
}

void handleSendMessage(int socketID, string message){
  transferMessage.ParseFromString(message);
  if (transferMessage.compresskind() == NoCompression)
    sendData(socketID, reinterpret_cast<void *>(transferMessage.pointer()),  transferMessage.size());
  else{
    size_t compressedSize = getMaxLength(transferMessage.size(), (cloudCompressionKind)transferMessage.compresskind());
    unsigned char *compressedData = static_cast<unsigned char *>(malloc(compressedSize));
    if (!compressedData) printf("Allocation is NULL\n");	
    compress(reinterpret_cast<unsigned char *>(transferMessage.pointer()), static_cast<size_t>(transferMessage.size()), compressedData, compressedSize, 1, (cloudCompressionKind)transferMessage.compresskind());
    sizeMessage.set_messagetype(SizeCommand);
    sizeMessage.set_size(compressedSize);
    sizeMessage.SerializeToString(&message);
    sendMessage(socketID, message);
    sendData(socketID, compressedData, compressedSize);
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

void handleCloseMessage(int socketID, int socketID2){
   close(socketID);
   close(socketID2);
}


void handleFreeMessage(string message){
   pointerMessage.ParseFromString(message);
   free(reinterpret_cast<void *>(pointerMessage.pointer()));
}


void MPIInitialize(MPIInfo & info){
    blacs_pinfo( &info.rank, &info.nProcs );

    int numthreads = 2;
    openblas_set_num_threads( numthreads );

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
     strg = charstr;
     delete [] charstr;
   }
 
   return;
}

void monitor(int portno){
    MPIInfo mpiInfo;
    MPIInitialize(mpiInfo);
    int sockfd, newsockfd;
    int commandKind;
    bool rootProc = (mpiInfo.rank == 0);
    
    if (rootProc) newsockfd = intitializeSocket(portno, sockfd);
      bool listen = true;
      while(listen){
	if (rootProc){
	  recMessage(newsockfd, message);
	  baseMessage.ParseFromString(message);	
	  commandKind = baseMessage.messagetype();
	}
	MPI_Bcast(&commandKind, 1, MPI_INT, 0, MPI_COMM_WORLD);
	switch(commandKind){
	  // Allocating in the memory
	  case AllocCommand:
	    if (rootProc) handleAllocationMessage(newsockfd, message);
	    break;
	  // Recieving the data from the client  
	  case GetCommand:
	    if (rootProc) handleGetMessage(newsockfd, message);
	    break;
	  // Sending data to the client  
	  case SendCommand:
	    if (rootProc) handleSendMessage(newsockfd, message);
	    break;
	  case FunctionCallCommand:
	    if (rootProc) recMessage(newsockfd, argsMessage);
	    broadcastString(rootProc, message);
	    broadcastString(rootProc, argsMessage);

	    printf("%d\n", message.size());
	    printf("%d\n", argsMessage.size());
/*	    for (int i = 0; i < message.size(); i++)
	      printf("%c ", message[i]);*/
//	    handleFunctionCallMessage(message, argsMessage, mpiInfo);
	    break;
	  // Freeing the memory
	  case FreeCommand:
	    if (rootProc) handleFreeMessage(message);
	    break;
	  // Closing the connection  
	  case CloseCommand:
	    if (rootProc) handleCloseMessage(newsockfd, sockfd);
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
