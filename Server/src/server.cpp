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
#include "cloudmessage.pb.h" 
using namespace std;
using namespace cloudmessaging;
using namespace google::protobuf;

PointerMessage pointerMessage;
SizeMessage sizeMessage;
TransferMessage transferMessage;
CommonMessage baseMessage;
string message;
char command[1000];



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


cloudError_t sendMessage(int socketID, string message){
    int n = write(socketID, command, 4);
    if (n < 0) return CloudErrorWrite;
    n = write(socketID, message.c_str(), message.size());
    if (n < 0) return CloudErrorWrite;
    return CloudSuccess;
}

cloudError_t recMessage(int socketID, string &message){
    int messageSize = 0;
    int n = read(socketID, &messageSize, 4);
    if (n !=4) return CloudErrorRead;
    n = write(socketID, command, messageSize);
    if (n < 0) return CloudErrorWrite;
    message = string(command);
    return CloudSuccess;
}

cloudError_t sendData(int socketID, const void * data, size_t size){
      int n = write(socketID, data, size);
      if (n < 0) return CloudErrorWrite;
      return CloudSuccess;
}

cloudError_t recData(int socketID, void * data, size_t size){
      unsigned int sent = 0;
      while (sent < size){
	int n = read(socketID, data + sent, size - sent);
	sent += n;
	if (n < 0) return CloudErrorRead;
      }
      return CloudSuccess;
}


int main(int argc, char *argv[])
{
    int sockfd, newsockfd, portno;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    portno = atoi(argv[1]);
    newsockfd = intitializeSocket(portno, sockfd);
    bool done = false;
    while(!done){
      recMessage(newsockfd, message);
      baseMessage.ParseFromString(message);
      int commandKind = baseMessage.messagetype();
      void * cloudPtr;
      size_t compressedSize;
      size_t outputSize;
      unsigned char * compressedData;
      std::pair<uint32_t, uint32_t> address;
      switch(commandKind){
	// Allocating in the memory
	case AllocCommand:
          sizeMessage.ParseFromString(message);
	  cloudPtr = malloc(sizeMessage.size());
	  pointerMessage.set_messagetype(PointerCommand);
	  pointerMessage.set_pointer((int64_t)(cloudPtr));
	  pointerMessage.SerializeToString(&message);
	  sendMessage(newsockfd, message);
	  break;
	// Recieving the data from the client  
	case GetCommand:
          transferMessage.ParseFromString(message);
	  if (transferMessage.compresskind() == NoCompression)
	    recData(newsockfd, (void *) transferMessage.pointer(),  transferMessage.size());
	  else{
	    compressedData = (unsigned char * )malloc(transferMessage.compressedsize());
	    if (!compressedData) printf("Allocation is NULL\n");	     
	    recData(newsockfd, (void *) compressedData,   transferMessage.compressedsize());
	    outputSize = (size_t)(transferMessage.size());
	    decompress(compressedData, transferMessage.compressedsize(), (unsigned char *)transferMessage.pointer(), outputSize, (cloudCompressionKind)transferMessage.compresskind());
	    free(compressedData);
	  }
	      
	  break;
	// Sending data to the client  
	case SendCommand:
          transferMessage.ParseFromString(message);
	  if (transferMessage.compresskind() == NoCompression)
	    sendData(newsockfd, (void *) transferMessage.pointer(),  transferMessage.size());
	  else{
	    compressedSize = getMaxLength(transferMessage.size(), (cloudCompressionKind)transferMessage.compresskind());
	    compressedData = (unsigned char * )malloc(compressedSize);
	    if (!compressedData) printf("Allocation is NULL\n");	
	    compress((unsigned char *)transferMessage.pointer(), (size_t)transferMessage.size(), compressedData, compressedSize, 1, (cloudCompressionKind)transferMessage.compresskind());
	    sizeMessage.set_messagetype(SizeCommand);
	    sizeMessage.set_size(compressedSize);
	    sizeMessage.SerializeToString(&message);
	    sendMessage(newsockfd, message);
	    sendData(newsockfd, compressedData, compressedSize);
	    free(compressedData);
	  }
	  break;
	// Freeing the memory
	case FreeCommand:
          pointerMessage.ParseFromString(message);
	  free((void *)pointerMessage.pointer());
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
