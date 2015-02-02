/*
 * $Id$
 */
#ifndef CLOUD_H
#  define CLOUD_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include "tcpSocket.h"
#include "compression.h"

cloudError_t cloudInit(int portno, char * hostname, TCPSocket & tcpSocket);
cloudError_t cloudFunctionCall(TCPSocket & tcpSocket, cloudFunctionKind functionType, std::string argsMessage);
cloudError_t cloudMalloc(TCPSocket & tcpSocket, void ** cloudPtr, size_t size);
cloudError_t cloudMemcpy(TCPSocket & tcpSocket,  void *  dst,  const void *  src,  size_t  count, enum cloudMemcpyKind directionKind, enum cloudCompressionKind compressKind);
cloudError_t cloudFree(TCPSocket & tcpSocket, void * cloudPtr);
cloudError_t cloudFinish(TCPSocket & tcpSocket);

#endif /* ifndef CLOUD_H */

