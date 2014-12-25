
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

int command[10];
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
    int n = write(socketID, &command, 8);
    if (n < 0)
      return CloudErrorWrite;
    void * cloudPtrFromCloud;
    n = read(socketID, &cloudPtrFromCloud, 4);
    if (n !=4)
      return CloudErrorRead;
    *cloudPtr =  cloudPtrFromCloud;
    return CloudSuccess;

}

cloudError_t cloudMemcpy(int socketID,  void *  dst,  const void *  src,  size_t  count,  enum cloudMemcpyKind	 kind ){
 
  if (kind == cloudMemcpyClientToCloud) {
    command[0] = GetCommand;
    command[1] = count;
    command[2] = (int)(dst);
    int n = write(socketID, &command, 12);
    if (n < 0)
      return CloudErrorWrite;
    n = write(socketID, src, count);
    if (n < 0)
      return CloudErrorWrite;
    
  }    
  else if (kind == cloudMemcpyCloudToClient) {
    command[0] = SendCommand;
    command[1] = count;
    command[2] = (int)(src);
    int n = write(socketID, &command, 12);
    if (n < 0)
      return CloudErrorWrite;
    int sent = 0;
    while (sent < count){
      n = read(socketID, dst + sent, count - sent);
      sent += n;
      if (n < 0){ 
	 return CloudErrorRead;
      }
    }

  }
  return CloudSuccess;
} 
//make it free
cloudError_t cloudFree(int socketID, void * cloudPtr){
    command[0] = FreeCommand;
    command[1] = (int)(cloudPtr);
    int n = write(socketID, &command, 8);
    if (n < 0)
      return CloudErrorWrite;
    return CloudSuccess;
}

cloudError_t cloudFinish( int socketID){
    command[0] = CloseCommand;
    int n = write(socketID, &command, 4);
    if (n < 0)
      return CloudErrorWrite;
    close(socketID);
    return CloudSuccess;
}


