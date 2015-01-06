#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <utility>
#include "cloud.h" 
#include "common.h" 
#include "cloudmessage.pb.h" 
#include "cloudTransfer.h" 
using namespace std;
using namespace cloudmessaging;

PointerMessage pointerMessage;
SizeMessage sizeMessage;
TransferMessage transferMessage;
FunctionCallMessage functionCallMessage;
string message;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}


// Initializing the connection
cloudError_t  cloudInit(int portno, char * hostname, int &socketID){
    struct sockaddr_in serv_addr;
    struct hostent *server;
    socketID = socket(AF_INET, SOCK_STREAM, 0);
    if (socketID < 0) return CloudErrorOpen;
    server = gethostbyname(hostname);
    if (server == NULL) return CloudErrorNoHost;
    bzero(reinterpret_cast<char *>(&serv_addr), sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy(static_cast<char *>(server->h_addr), 
         reinterpret_cast<char *>(&serv_addr.sin_addr.s_addr),
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(socketID,reinterpret_cast<struct sockaddr *>( &serv_addr),sizeof(serv_addr)) < 0) 
        return CloudErrorConnection;
    return CloudSuccess;
}

cloudError_t  cloudFunctionCall(int socketID, cloudFunctionKind functionType, std::string argsMessage){
   functionCallMessage.set_messagetype(FunctionCallCommand);
   printf("Function kind is %d\n", functionType);
   functionCallMessage.set_functiontype(functionType);
   functionCallMessage.SerializeToString(&message);
   sendMessage(socketID, message);
   sendMessage(socketID, argsMessage);
   return CloudSuccess;

}

// Allocating an array with size in the server. 
cloudError_t cloudMalloc(int socketID, void ** cloudPtr, size_t size){
    sizeMessage.set_messagetype(AllocCommand);
    sizeMessage.set_size(size);
    sizeMessage.SerializeToString(&message);
    sendMessage(socketID, message);
    recMessage(socketID, message);
    pointerMessage.ParseFromString(message);
    *cloudPtr =  reinterpret_cast<void *> (pointerMessage.pointer());
    return CloudSuccess;
}

// cloudMemcpy is transferring data between client and the server
cloudError_t cloudMemcpy(int socketID,  void *  dst,  const void *  src,  size_t  count,   enum cloudMemcpyKind	 directionKind, enum cloudCompressionKind compressKind){
 
  if (compressKind != NoCompression){
    if (directionKind == cloudMemcpyClientToCloud) {
      size_t compressedSize= getMaxLength( count, compressKind); 
      unsigned char * out  = static_cast<unsigned char *>(malloc(compressedSize));
      compress(static_cast<const unsigned char *>(src), count, out, compressedSize, 1, compressKind);

      transferMessage.set_messagetype(GetCommand);
      transferMessage.set_compresskind(compressKind);
      transferMessage.set_size(count);
      transferMessage.set_compressedsize(compressedSize);
      transferMessage.set_pointer(reinterpret_cast<int64_t>(dst));
      transferMessage.SerializeToString(&message);
      
      sendMessage(socketID, message);
      sendData(socketID, out, compressedSize);
      free(out);
    }    
    else if (directionKind == cloudMemcpyCloudToClient) {
      transferMessage.set_messagetype(SendCommand);
      transferMessage.set_compresskind(compressKind);
      transferMessage.set_size(count);
      transferMessage.set_compressedsize(0);
      transferMessage.set_pointer(reinterpret_cast<int64_t>(src));
      transferMessage.SerializeToString(&message);
      
      sendMessage(socketID, message);
      recMessage(socketID, message);
      
      sizeMessage.ParseFromString(message);
      size_t compressedSize =  static_cast<size_t>(sizeMessage.size());
      unsigned char * out  = static_cast<unsigned char *>(malloc(compressedSize * sizeof(char)));
      recData(socketID, out, compressedSize);
      decompress(out, compressedSize, static_cast<unsigned char *>(dst), count, compressKind);
      free(out);
    }
  }
  else{
    if (directionKind == cloudMemcpyClientToCloud) {
      transferMessage.set_messagetype(GetCommand);
      transferMessage.set_compresskind(NoCompression);
      transferMessage.set_size(count);
      transferMessage.set_compressedsize(0);
      transferMessage.set_pointer(reinterpret_cast<int64_t>(dst));
      transferMessage.SerializeToString(&message);
      sendMessage(socketID, message);
      sendData(socketID, src, count);
    }  
    else if (directionKind == cloudMemcpyCloudToClient) {
      transferMessage.set_messagetype(SendCommand);
      transferMessage.set_compresskind(NoCompression);
      transferMessage.set_size(count);
      transferMessage.set_compressedsize(0);
      transferMessage.set_pointer(reinterpret_cast<int64_t>(src));
      transferMessage.SerializeToString(&message);
      sendMessage(socketID, message);
      recData(socketID, dst, count);
    }
  }
  return CloudSuccess;
} 

// Freeing the array on the cloud
cloudError_t cloudFree(int socketID, void * cloudPtr){
    pointerMessage.set_messagetype(FreeCommand);
    pointerMessage.set_pointer(reinterpret_cast<int64_t>(cloudPtr));
    pointerMessage.SerializeToString(&message);
    return sendMessage(socketID, message);
}

// Finishing the connection
cloudError_t cloudFinish( int socketID){
    sizeMessage.set_messagetype(CloseCommand);
    sizeMessage.set_size(0);
    sizeMessage.SerializeToString(&message);
    sendMessage(socketID, message);
    close(socketID);
    return CloudSuccess; 
}


