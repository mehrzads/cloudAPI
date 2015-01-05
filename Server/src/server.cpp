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
#include "cloudTransfer.h"
using namespace std;
using namespace cloudmessaging;
using namespace google::protobuf;

PointerMessage pointerMessage;
SizeMessage sizeMessage;
TransferMessage transferMessage;
CommonMessage baseMessage;
string message;



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


void handleCloseMessage(int socketID, int socketID2){
   close(socketID);
   close(socketID2);
}


void handleFreeMessage(string message){
   pointerMessage.ParseFromString(message);
   free(reinterpret_cast<void *>(pointerMessage.pointer()));
}

void monitor(int portno){
    int sockfd, newsockfd;
    newsockfd = intitializeSocket(portno, sockfd);
    bool listen = true;
    while(listen){
      recMessage(newsockfd, message);
      baseMessage.ParseFromString(message);
      int commandKind = baseMessage.messagetype();
      switch(commandKind){
	// Allocating in the memory
	case AllocCommand:
	  handleAllocationMessage(newsockfd, message);
	  break;
	// Recieving the data from the client  
	case GetCommand:
	  handleGetMessage(newsockfd, message);
	  break;
	// Sending data to the client  
	case SendCommand:
	  handleSendMessage(newsockfd, message);
	  break;
	// Freeing the memory
	case FreeCommand:
	  handleFreeMessage(message);
	  break;
	// Closing the connection  
	case CloseCommand:
	  handleCloseMessage(newsockfd, sockfd);
	  listen = false;
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
