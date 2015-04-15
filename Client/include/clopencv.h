/*
 * $Id$
 */
#ifndef CLOPENCV_H
#  define CLOPENCV_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "tcpSocket.h"

cloudError_t cloudFaceTrain(TCPSocket & socketID, int rows, int cols, 
    char * images, int *  labels, double * eigenValues, double * eigenVectors, double * mean); 


#endif /* ifndef CLOPENCV_H */

