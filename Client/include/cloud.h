/*
 * $Id$
 */
#ifndef CLOUD_H
#  define CLOUD_H

#include "common.h"
#include "compression.h"

cloudError_t cloudInit(int portno, char * hostname, int &socketID);
cloudError_t cloudMalloc(int socketID, void ** cloudPtr, size_t size);
cloudError_t cloudMemcpy(int socketID,  void *  dst,  const void *  src,  size_t  count,    enum cloudMemcpyKind	 kind );
cloudError_t cloudFree(int socketID, void * cloudPtr);
cloudError_t cloudFinish( int socketID);

#endif /* ifndef CLOUD_H */

