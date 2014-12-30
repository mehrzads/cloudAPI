
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

uint32_t command[10];
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


//Initializing the connection
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
    command[0] = AllocCommand;
    command[1] = size;
    int n = write(socketID, command, 8);
    if (n < 0) return CloudErrorWrite;
    n = read(socketID, command, 8);
    if (n !=8) return CloudErrorRead;
    *cloudPtr =  (void *) ((((long int)command[0]) <<32) | command[1]);
    return CloudSuccess;
}

//cloudMemcpy is transferring data between client and the server
//It has 4 different cases:
//compressed, ToServer
//compressed, FromServer
//nonCompressed, ToServer
//nonCompressed, FromServer 
cloudError_t cloudMemcpy(int socketID,  void *  dst,  const void *  src,  size_t  count,   enum cloudMemcpyKind	 kind , bool isCompressed){
 
  if (isCompressed){
    //compressed, ToServer
    // Command which is send to the server:
    // 5 words: CmdIndex, count, compressedSize, pointer
    // Then client will send the data to the server
    // compressedSize words
    if (kind == cloudMemcpyClientToCloud) {
      size_t compressedSize= getMaxLength( count); 
      unsigned char * out  = (unsigned char *) malloc(compressedSize);
      compress((const unsigned char *)src, count, out, compressedSize, 1);
      printf("GetCompressedData\t%d\t%d\n", count, compressedSize);
      command[0] = GetCompressedCommand;
      command[1] =  count;
      command[2] =  compressedSize;
      std::pair<uint32_t, uint32_t> address = convert64to32(dst);
      command[3] = address.first;
      command[4] = address.second;
      int n = write(socketID, command, 20);
      if (n < 0) return CloudErrorWrite;
      n = write(socketID, out, compressedSize);
      if (n < 0) return CloudErrorWrite;
      free(out);
    }    
    //compressed, ToServer
    // Command which is send to the server:
    // 5 words: CmdIndex, count, compressedSize, pointer
    // Then client will send the data to the server
    // compressedSize words
    else if (kind == cloudMemcpyCloudToClient) {
      printf("We are here\n");
      command[0] = SendCompressedCommand;
      command[1] = count;
      std::pair<uint32_t, uint32_t> address = convert64to32(src);
      command[2] = address.first;
      command[3] = address.second;
      int n = write(socketID, command, 16);
      if (n < 0) return CloudErrorWrite;
      n = read(socketID, command, 4);
      if (n < 0) return CloudErrorRead;
      size_t compressedSize = command[0]; 
      printf("SendCompressedData\t%d\t%d\n", count, compressedSize);
      unsigned int sent = 0;
      unsigned char * out  = (unsigned char *) malloc(compressedSize * sizeof(char));
      while (sent < compressedSize){
	n = read(socketID, out + sent, compressedSize - sent);
	sent += n;
	if (n < 0) return CloudErrorRead;
      }
      decompress(out, compressedSize, (unsigned char *)dst, count);
      free(out);
    }
  }
  else{
    if (kind == cloudMemcpyClientToCloud) {
      command[0] = GetCommand;
      command[1] =  count;
      std::pair<uint32_t, uint32_t> address = convert64to32(dst);
      command[2] = address.first;
      command[3] = address.second;
      int n = write(socketID, command, 16);
      if (n < 0) return CloudErrorWrite;
      n = write(socketID, src, count);
      if (n < 0) return CloudErrorWrite;
    }    
    else if (kind == cloudMemcpyCloudToClient) {
      command[0] = SendCommand;
      command[1] = count;
      std::pair<uint32_t, uint32_t> address = convert64to32(src);
      command[2] = address.first;
      command[3] = address.second;
      int n = write(socketID, command, 16);
      if (n < 0) return CloudErrorWrite;
      unsigned int sent = 0;
      while (sent < count){
	n = read(socketID, dst + sent, count - sent);
	sent += n;
	if (n < 0) return CloudErrorRead;
      }
    }
  }
  return CloudSuccess;
} 
//make it free
cloudError_t cloudFree(int socketID, void * cloudPtr){
    command[0] = FreeCommand;
    std::pair<uint32_t, uint32_t> address = convert64to32(cloudPtr);
    command[1] = address.first;
    command[2] = address.second;
    int n = write(socketID, command, 12);
    if (n < 0) return CloudErrorWrite;
    return CloudSuccess;
}

cloudError_t cloudFinish( int socketID){
    command[0] = CloseCommand;
    int n = write(socketID, command, 4);
    if (n < 0) return CloudErrorWrite;
    close(socketID);
    return CloudSuccess;
}


