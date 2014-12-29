
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "cloud.h" 
#include "common.h" 

unsigned int command[10];
void error(const char *msg)
{
    perror(msg);
    exit(0);
}
cloudError_t  cloudInit(int portno, char * hostname, int &socketID){

    struct sockaddr_in serv_addr;
    struct hostent *server;
    socketID = socket(AF_INET, SOCK_STREAM, 0);
    if (socketID < 0) 
        return CloudErrorOpen;
    server = gethostbyname(hostname);
    if (server == NULL) {
	return CloudErrorNoHost;
    }
    //setting up a socket
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


cloudError_t cloudMalloc(int socketID, void ** cloudPtr, size_t size){
    command[0] = AllocCommand;
    command[1] = size;
    int n = write(socketID, command, 8);
    if (n < 0)
      return CloudErrorWrite;
    n = read(socketID, command, 8);
    if (n !=8)
      return CloudErrorRead;
    *cloudPtr =  (void *) ((((long int)command[0]) <<32) | command[1]);
    return CloudSuccess;

}

cloudError_t cloudMemcpy(int socketID,  void *  dst,  const void *  src,  size_t  count,   enum cloudMemcpyKind	 kind ){
 
  if (kind == cloudMemcpyClientToCloud) {
    
//    unsigned char * out  = (unsigned char *) malloc(count);
//    compress((unsigned char *)src, count, out, compressedSize, 9);
//    printf("How many bytes?%d\t%d\n", count, compressedSize);
    command[0] = GetCommand;
    command[1] =  count;
    unsigned int x = (unsigned int)(( ((long unsigned)dst) & 0xFFFFFFFF00000000) >> 32);
    unsigned int y = (unsigned int)(((long unsigned)dst) & 0xFFFFFFFF);
    command[2] = x;
    command[3] = y;
    int n = write(socketID, command, 16);
    if (n < 0)
      return CloudErrorWrite;
    n = write(socketID, src, count);
   // n = write(socketID, out, compressedSize);
    if (n < 0)
      return CloudErrorWrite;
  //  free(out);
    
  }    
  else if (kind == cloudMemcpyCloudToClient) {
    command[0] = SendCommand;
    command[1] = count;//compressedSize;
    unsigned int x = (unsigned int)(( ((long unsigned)src) & 0xFFFFFFFF00000000) >> 32);
    unsigned int y = (unsigned int)(((long unsigned)src) & 0xFFFFFFFF);
    command[2] = x;
    command[3] = y;
    int n = write(socketID, command, 16);
    if (n < 0)
      return CloudErrorWrite;
    unsigned int sent = 0;
//    unsigned char * out  = (unsigned char *) malloc(compressedSize * sizeof(char));
    while (sent < count){
      n = read(socketID, dst + sent, count - sent);
//      n = read(socketID, out + sent, compressedSize - sent);
      sent += n;
      if (n < 0){ 
	 return CloudErrorRead;
      }
    }

 //   decompress(out, compressedSize, (unsigned char *)dst, count);
  //  free(out);

  }
  return CloudSuccess;
} 
//make it free
cloudError_t cloudFree(int socketID, void * cloudPtr){
    command[0] = FreeCommand;
    unsigned int x = (unsigned int)(( (long unsigned)cloudPtr & 0xFFFFFFFF00000000) >> 32);
    unsigned int y = (unsigned int)((long unsigned)cloudPtr & 0xFFFFFFFF);
    command[1] = x;
    command[2] = y;
    int n = write(socketID, command, 12);
    if (n < 0)
      return CloudErrorWrite;
    return CloudSuccess;
}

cloudError_t cloudFinish( int socketID){
    command[0] = CloseCommand;
    int n = write(socketID, command, 4);
    if (n < 0)
      return CloudErrorWrite;
    close(socketID);
    return CloudSuccess;
}


