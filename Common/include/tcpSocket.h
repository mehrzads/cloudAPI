/*
 * $Id$
 */
#ifndef TCPSOCKET_H
#  define TCPSOCKET_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include "common.h"
#define MAXTHREADS 16

class TCPSocket {
  private:
    char command[1000];
    unsigned int nThreads;
    int sockets[MAXTHREADS];
    int origSockets[MAXTHREADS];
    pthread_t *threads;
    bool isServer;
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
    cloudError_t sendData(const void * data, size_t size);
    cloudError_t recData(void * data, size_t size);
    
    cloudError_t clientConnect(int portno, char * hostname);
    cloudError_t serverListen(int portno);
    cloudError_t closeSocket();
};

#endif /* ifndef TCPSOCKET_H */

