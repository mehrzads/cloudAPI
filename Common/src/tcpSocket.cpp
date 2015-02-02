#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>
#include "tcpSocket.h"

using namespace std;
void error(const char *msg)
{
    perror(msg);
    exit(1);
}
TCPSocket::TCPSocket(): 
      nThreads (1)
{
  threads =(pthread_t *) malloc(MAXTHREADS * sizeof(pthread_t));
  threadArg = (struct ThreadArg *) malloc(MAXTHREADS * sizeof(struct ThreadArg));
} 

TCPSocket::TCPSocket(unsigned int n): 
      nThreads (n)
{
  threads =(pthread_t *) malloc(MAXTHREADS * sizeof(pthread_t));
} 

void TCPSocket::setnThreads(unsigned int n){
  nThreads = n;
}

unsigned int TCPSocket::getnThreads() const {
  return nThreads;
}

void TCPSocket::setSocket(int socket, unsigned int index){
  sockets[index] = socket;
}

int TCPSocket::getSocket(unsigned int index) const {
  return sockets[index];
}


TCPSocket::~TCPSocket(){
  if (threads)
    free(threads);
}


cloudError_t TCPSocket::sendMessage(std::string message){
  int socketID = getSocket(0);
  int messageSize = message.size();
  int n = write(socketID, &messageSize, 4);
  if (n < 0) return CloudErrorWrite;
  n = write(socketID, message.c_str(), message.size());
  if (n < 0) return CloudErrorWrite;
  return CloudSuccess;
}

cloudError_t TCPSocket::recMessage(std::string &message){
  int socketID = getSocket(0);
  int messageSize = 0;
  int n = read(socketID, &messageSize, 4);
  if (n <0) return CloudErrorRead;
  n = read(socketID, command, messageSize);
  if (n < 0) return CloudErrorRead;
  message = std::string(command, messageSize);
  return CloudSuccess;
}

cloudError_t TCPSocket::sendStreamData( int socketID, char * data, size_t size){
  register size_t sent = 0;
  register size_t n = 0;
  while (sent < size){
    n = write(socketID, data + sent, size - sent);
    if (n < 0) return CloudErrorWrite;
    sent += n;
  }
  return CloudSuccess;
}

cloudError_t TCPSocket::recStreamData(int socketID, char * data, size_t size){
  register size_t sent = 0;
  register size_t n = 0;
//  char *  buf = static_cast<char *>(data);
  while (sent < size){
    //static casts are added to remove the warning
    n = read(socketID, data + sent, size - sent);
    sent += n;
    if (n < 0) return CloudErrorRead;
  }
  return CloudSuccess;
}

void *TCPSocket::sendThread(void *arg){
  struct ThreadArg* tArg =   ((struct ThreadArg*)arg);
  size_t start = tArg->ID * tArg-> step;
  size_t step = min(tArg-> step, tArg->size - start);
  sendStreamData(tArg->socket,  tArg->data + start,  step);
  return NULL;
}

void *TCPSocket::recThread(void *arg){
  struct ThreadArg* tArg =   ((struct ThreadArg*)arg);
  size_t start = tArg->ID * tArg-> step;
  size_t step = min(tArg-> step, tArg->size - start);
  recStreamData(tArg->socket,  tArg->data + start,  step);
  return NULL;
}

cloudError_t TCPSocket::sendData( void * data, size_t size){
   size_t step = size / nThreads;
   int thread_cr_res = 0, thread_join_res;

  for(unsigned int i = 0; i < nThreads; i++){
    threadArg[i].data = static_cast<char *>(data);
    threadArg[i].size = size * sizeof(float);
    threadArg[i].step = step;
    threadArg[i].socket = sockets[i];
    threadArg[i].ID = i;
    thread_cr_res = pthread_create(&threads[i], NULL, sendThread, (void*)(&threadArg[i]));
    if(thread_cr_res != 0){
      fprintf(stderr,"THREAD CREATE ERROR");
      return CloudSuccess;
    }
  }
  /* Later edit, joining the threads */
  for (unsigned int i = 0; i < nThreads; i++){
    thread_join_res = pthread_join(threads[i], NULL);
    if(thread_join_res != 0){
      fprintf(stderr, "JOIN ERROR");
      return CloudSuccess;
    }       
  }
      return CloudSuccess;
}

cloudError_t TCPSocket::recData(void * data, size_t size){
   size_t step = size / nThreads;

   int thread_cr_res = 0, thread_join_res;
  for(unsigned int i = 0; i < nThreads; i++){
    threadArg[i].data = static_cast<char *>(data);
    threadArg[i].size = size * sizeof(float);
    threadArg[i].step = step;
    threadArg[i].socket = sockets[i];
    threadArg[i].ID = i;
    thread_cr_res = pthread_create(&threads[i], NULL, recThread, (void*)(&threadArg[i]));
    if(thread_cr_res != 0){
      fprintf(stderr,"THREAD CREATE ERROR");
      return CloudSuccess;
    }
  }
  /* Later edit, joining the threads */
  for (unsigned int i = 0; i < nThreads; i++){
    thread_join_res = pthread_join(threads[i], NULL);
    if(thread_join_res != 0){
      fprintf(stderr, "JOIN ERROR");
      return CloudSuccess;
    }       
  }
      return CloudSuccess;
}


cloudError_t TCPSocket::clientConnect(int portno, char * hostname){
    isServer = false;
    for (unsigned int i = 0; i < getnThreads(); i++){
      struct sockaddr_in serv_addr;
      struct hostent *server;
      int socketID = socket(AF_INET, SOCK_STREAM, 0);
      if (socketID < 0) return CloudErrorOpen;
      server = gethostbyname(hostname);
      if (server == NULL) return CloudErrorNoHost;
      bzero(reinterpret_cast<char *>(&serv_addr), sizeof(serv_addr));
      serv_addr.sin_family = AF_INET;
      bcopy(static_cast<char *>(server->h_addr), 
	   reinterpret_cast<char *>(&serv_addr.sin_addr.s_addr),
	   server->h_length);
      serv_addr.sin_port = htons(portno + i);
      if (connect(socketID,reinterpret_cast<struct sockaddr *>( &serv_addr),sizeof(serv_addr)) < 0) 
	  return CloudErrorConnection;
      setSocket(socketID, i);
    }
    return CloudSuccess;
}

cloudError_t TCPSocket::serverListen(int portno){
    isServer = true;
    for (unsigned int i = 0; i < getnThreads(); i++){
      socklen_t clilen;
      struct sockaddr_in serv_addr, cli_addr;
      origSockets[i] = socket(AF_INET, SOCK_STREAM, 0);
      if (origSockets[i] < 0) error("ERROR opening socket");
      bzero((char *) &serv_addr, sizeof(serv_addr));
      serv_addr.sin_family = AF_INET;
      serv_addr.sin_addr.s_addr = INADDR_ANY;
      serv_addr.sin_port = htons(portno + i);
      if (bind(origSockets[i], reinterpret_cast<struct sockaddr *>(&serv_addr),
	       sizeof(serv_addr)) < 0) 
	       error("ERROR on binding");
      listen(origSockets[i],5);
      clilen = sizeof(cli_addr);
      sockets[i] = accept(origSockets[i], 
		  reinterpret_cast<struct sockaddr *>(&cli_addr), 
		  &clilen);
      if (sockets[i] < 0) error("ERROR on accept");
    }
    return CloudSuccess;
}

cloudError_t TCPSocket::closeSocket(){
  for (unsigned int i = 0; i < getnThreads(); i++)
    close(sockets[i]);
  if (isServer){
    for (unsigned int i = 0; i < getnThreads(); i++)
      close(origSockets[i]);
  }
    return CloudSuccess;

}
