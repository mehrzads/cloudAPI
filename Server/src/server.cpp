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
#include <utility>
#include "common.h"
#include "compression.h"



void error(const char *msg)
{
    perror(msg);
    exit(1);
}

// Converting pointer to the 4 bytes integers so we can send them to the server
std::pair<uint32_t, uint32_t> convert64to32(const void * pointer){
      uint32_t x = (uint32_t)(( ((uint64_t)pointer) & 0xFFFFFFFF00000000) >> 32);
      uint32_t y = (uint32_t)(((uint64_t)pointer) & 0xFFFFFFFF);
      return std::make_pair(x,y);
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
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
             error("ERROR on binding");
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
    int newsockfd = accept(sockfd, 
                (struct sockaddr *) &cli_addr, 
                &clilen);
    if (newsockfd < 0) error("ERROR on accept");
    return newsockfd;
    
}

// Transferring to the client
bool memcpyToCloud(int sockfd, const void * src, size_t count){

    int n = write(sockfd, src, count);
    if (n < 0){ 
         error("ERROR writing to socket");
	 return false;
    }
    return true;
}


// Transferring from the client
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
    uint32_t command[10];
    newsockfd = intitializeSocket(portno, sockfd);
    bool done = false;
    while(!done){
      cloudCommandKind commandKind;
      //Read the command index
      memcpyFromCloud(newsockfd, &commandKind, 4);
      int size = 0;
      int count = 0;
      size_t compressedSize;
      size_t outputSize;
      unsigned char * compressedData;
      enum cloudCompressionKind compressionKind;
      std::pair<uint32_t, uint32_t> address;
      void * cloudPtr;
      switch(commandKind){
	// Allocating in the memory
	case AllocCommand:
	  memcpyFromCloud(newsockfd, command, 4);
	  size = command[0];
	  cloudPtr = malloc(size);
          address = convert64to32(cloudPtr);
          command[0] = address.first;
          command[1] = address.second;
	  memcpyToCloud(newsockfd, command, 8);
	  break;
	// Recieving the data from the client  
	case GetCommand:
	  memcpyFromCloud(newsockfd, command, 12);
	  count = command[0];
	  cloudPtr =  (void *) ((((long int)command[1]) <<32) | command[2]);
	  memcpyFromCloud(newsockfd, cloudPtr, count);
	  break;
	// Sending data to the client  
	case SendCommand:
	  memcpyFromCloud(newsockfd, command, 12);
	  count = command[0];
	  cloudPtr =  (void *) ((((long int)command[1]) <<32) | command[2]);
	  memcpyToCloud(newsockfd, cloudPtr, count);
	  break;
	// Recieving the compressed data from the client  
	case GetCompressedCommand:
	  memcpyFromCloud(newsockfd, command, 20);
	  compressionKind  = static_cast<cloudCompressionKind>(command[0]);
	  count = command[1];
	  compressedSize = command[2];
	  cloudPtr =  (void *) ((((long int)command[3]) <<32) | command[4]);
	  compressedData = (unsigned char * )malloc(compressedSize);
	  if (!compressedData) printf("Allocation is NULL\n");	
	  memcpyFromCloud(newsockfd, (void *) compressedData, compressedSize);
	  outputSize = (size_t)count;
	  decompress(compressedData, compressedSize, (unsigned char *)cloudPtr, outputSize, compressionKind);
	  free(compressedData);
	  break;
	// Sending compressed data to the client  
	case SendCompressedCommand:
	  memcpyFromCloud(newsockfd, command, 16);
	  compressionKind  = static_cast<cloudCompressionKind>(command[0]);
	  count = command[1];
	  cloudPtr =  (void *) ((((long int)command[2]) <<32) | command[3]);
	  compressedSize = getMaxLength(count, compressionKind);
	  compressedData = (unsigned char * )malloc(compressedSize);
	  compress((unsigned char *)cloudPtr, count, compressedData, compressedSize, 1, compressionKind);
	  if (!compressedData) printf("Allocation is NULL\n");	
	  command[0] = compressedSize;
	  memcpyToCloud(newsockfd, command, 4);
	  memcpyToCloud(newsockfd, compressedData, compressedSize);
	  free(compressedData);
	  break;
	// Freeing the memory
	case FreeCommand:
	  memcpyFromCloud(newsockfd, command, 8);
	  cloudPtr =  (void *) ((((long int)command[0]) <<32) | command[1]);
	  free(cloudPtr);
	  break;
	// Closing the connection  
	case CloseCommand:
	  close(newsockfd);
	  close(sockfd);
	  done = true;
	  break;
      }
    }

    return 0; 
}
