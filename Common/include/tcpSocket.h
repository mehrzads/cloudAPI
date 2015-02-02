/*
 * $Id$
 */
#ifndef TCPSOCKET_H
#  define TCPSOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <pthread.h>
#include "common.h"
#define MAXTHREADS 16

class TCPSocket {
  private:
    struct ThreadArg {
	 char * data;
	 size_t size;
	 size_t step;
	 int socket;
	 int ID;
    };
    char command[1000];
    unsigned int nThreads;
    int sockets[MAXTHREADS];
    int origSockets[MAXTHREADS];
    pthread_t *threads;
    bool isServer;
    ThreadArg * threadArg;

    static cloudError_t sendStreamData( int socketID, char * data, size_t size);
    static cloudError_t recStreamData(int socketID, char * data, size_t size);
    static void *sendThread(void *arg);
    static void *recThread(void *arg);
  public:
    TCPSocket();
    TCPSocket(unsigned int n);
    ~TCPSocket();

    void setnThreads(unsigned int n);
    unsigned int  getnThreads() const;
    
    void setSocket(int socket, unsigned int index);
    int  getSocket(unsigned int index) const;
    
    cloudError_t sendMessage(std::string message);
    cloudError_t recMessage(std::string &message);
    cloudError_t sendData(void * data, size_t size);
    cloudError_t recData(void * data, size_t size);
    
    cloudError_t clientConnect(int portno, char * hostname);
    cloudError_t serverListen(int portno);
    cloudError_t closeSocket();
};

#endif /* ifndef TCPSOCKET_H */

