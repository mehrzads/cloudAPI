
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
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
string message;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

// Converting pointer to the 4 bytes integers so we can send them to the server
std::pair<uint32_t, uint32_t> convert64to32(const void * pointer){
      uint32_t x = (uint32_t)(( ((uint64_t)pointer) & 0xFFFFFFFF00000000) >> 32);
      uint32_t y = (uint32_t)(((uint64_t)pointer) & 0xFFFFFFFF);
      return std::make_pair(x,y);
}


// Initializing the connection
cloudError_t  cloudInit(int portno, char * hostname, int &socketID){
    struct sockaddr_in serv_addr;
    struct hostent *server;
    socketID = socket(AF_INET, SOCK_STREAM, 0);
    if (socketID < 0) return CloudErrorOpen;
    server = gethostbyname(hostname);
    if (server == NULL) return CloudErrorNoHost;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(socketID,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        return CloudErrorConnection;
    return CloudSuccess;
}


// Allocating an array with size in the server. 
// Cloudptr is the pointer that is allocated on the server
// Command which is send to the server:
// 2 words: CmdIndex, Size
// In return server will reply back 2 bytes:
// 2 Words: Pointer
cloudError_t cloudMalloc(int socketID, void ** cloudPtr, size_t size){
    sizeMessage.set_messagetype(AllocCommand);
    sizeMessage.set_size(size);
    sizeMessage.SerializeToString(&message);
    print(message);
    sendMessage(socketID, message);
    recMessage(socketID, message);
    pointerMessage.ParseFromString(message);
    *cloudPtr =  (void *) (pointerMessage.pointer());
    return CloudSuccess;
}

// cloudMemcpy is transferring data between client and the server
cloudError_t cloudMemcpy(int socketID,  void *  dst,  const void *  src,  size_t  count,   enum cloudMemcpyKind	 directionKind, enum cloudCompressionKind compressKind){
 
  if (compressKind != NoCompression){
    if (directionKind == cloudMemcpyClientToCloud) {
      size_t compressedSize= getMaxLength( count, compressKind); 
      unsigned char * out  = (unsigned char *) malloc(compressedSize);
      compress((const unsigned char *)src, count, out, compressedSize, 1, compressKind);

      transferMessage.set_messagetype(GetCommand);
      transferMessage.set_compresskind(compressKind);
      transferMessage.set_size(count);
      transferMessage.set_compressedsize(compressedSize);
      transferMessage.set_pointer((int64_t)dst);
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
      transferMessage.set_pointer((int64_t)src);
      transferMessage.SerializeToString(&message);
      sendMessage(socketID, message);
      recMessage(socketID, message);
      sizeMessage.ParseFromString(message);
      size_t compressedSize =  (size_t)sizeMessage.size();
      unsigned char * out  = (unsigned char *) malloc(compressedSize * sizeof(char));
      recData(socketID, out, compressedSize);
      decompress(out, compressedSize, (unsigned char *)dst, count, compressKind);
      free(out);
    }
  }
  else{

    // Uncompressed, ToServer
    // Command which is send to the server:
    // 4 words: CmdIndex, count, pointer
    // Then client will send the data to the server
    // count words
    if (directionKind == cloudMemcpyClientToCloud) {
      transferMessage.set_messagetype(GetCommand);
      transferMessage.set_compresskind(NoCompression);
      transferMessage.set_size(count);
      transferMessage.set_compressedsize(0);
      transferMessage.set_pointer((int64_t)dst);
      transferMessage.SerializeToString(&message);
      sendMessage(socketID, message);
      sendData(socketID, src, count);
    }  

    // Uncompressed, FromServer
    // Command which is send to the server:
    // 4 words: CmdIndex, count, pointer
    // Then client will receive the data to the server
    // count words
    else if (directionKind == cloudMemcpyCloudToClient) {
      transferMessage.set_messagetype(SendCommand);
      transferMessage.set_compresskind(NoCompression);
      transferMessage.set_size(count);
      transferMessage.set_compressedsize(0);
      transferMessage.set_pointer((int64_t)src);
      transferMessage.SerializeToString(&message);
      sendMessage(socketID, message);
      recData(socketID, dst, count);
    }
  }
  return CloudSuccess;
} 

// Freeing the array on the cloud
cloudError_t cloudFree(int socketID, void * cloudPtr){
    printf("Free\n");
    pointerMessage.set_messagetype(FreeCommand);
    pointerMessage.set_pointer((int64_t)(cloudPtr));
    pointerMessage.SerializeToString(&message);
    print(message);
    return sendMessage(socketID, message);
}

// Finishing the connection
cloudError_t cloudFinish( int socketID){
    printf("Close\n");
    sizeMessage.set_messagetype(CloseCommand);
    sizeMessage.set_size(0);
    sizeMessage.SerializeToString(&message);
    sendMessage(socketID, message);
    close(socketID);
    return CloudSuccess; 
}


