/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <chrono>
#include "common.h"



void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int intitializeSocket(int portno, int &sockfd){

    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
      error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
             error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    int newsockfd = accept(sockfd, 
                (struct sockaddr *) &cli_addr, 
                &clilen);
    if (newsockfd < 0) 
         error("ERROR on accept");
    return newsockfd;
    
}


bool memcpyToCloud(int sockfd, const void * src, size_t count){

    int n = write(sockfd, src, count);
    if (n < 0){ 
         error("ERROR writing to socket");
	 return false;
    }
    return true;
}



bool memcpyFromCloud(int sockfd, void * dst,  size_t count){
    unsigned int sent = 0;
    while(sent < count){
      int n = read(sockfd, dst + sent, count - sent);
      sent += n;
      if (n < 0){ 
         error("ERROR reading from socket");
	 return false;
      }
    }
    return true;
}


int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    portno = atoi(argv[1]);
    unsigned int command[10];
    
    newsockfd = intitializeSocket(portno, sockfd);
    bool done = false;
    while(!done){
    cloudCommandKind commandKind;
    memcpyFromCloud(newsockfd, &commandKind, 4);

    int size = 0;
    int count = 0;
    void * cloudPtr;
    unsigned int x;
    unsigned int y;

    switch(commandKind){
      case AllocCommand:
	memcpyFromCloud(newsockfd, command, 4);
	size = command[0];
	cloudPtr = malloc(size);
 	x = (unsigned int)(( ((long unsigned)cloudPtr) & 0xFFFFFFFF00000000) >> 32);
 	y = (unsigned int)(((long unsigned)cloudPtr) & 0xFFFFFFFF);
	command[0] = x;
	command[1] = y;
	memcpyToCloud(newsockfd, command, 8);
	break;
      case GetCommand:
	memcpyFromCloud(newsockfd, command, 12);
	count = command[0];
	cloudPtr =  (void *) ((((long int)command[1]) <<32) | command[2]);
	memcpyFromCloud(newsockfd, cloudPtr, count);
	break;
      case SendCommand:
	memcpyFromCloud(newsockfd, command, 12);
	count = command[0];
	cloudPtr =  (void *) ((((long int)command[1]) <<32) | command[2]);
	memcpyToCloud(newsockfd, cloudPtr, count);
	break;
      case FreeCommand:
	memcpyFromCloud(newsockfd, command, 8);
	cloudPtr =  (void *) ((((long int)command[0]) <<32) | command[1]);
	free(cloudPtr);
	break;
      case CloseCommand:
	close(newsockfd);
	close(sockfd);
	done = true;
	break;
    }
}

    return 0; 
}
