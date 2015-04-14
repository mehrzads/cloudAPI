/*
 * $Id$
 */
#ifndef CLOPENCV_H
#  define CLOPENCV_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include "server.h"

cloudError_t cloudFaceTrain(int rows, int cols,
    char * images,
    int * labels,
    MPIInfo mpiInfo);

cloudError_t handleClOpenCVFunction(cloudFunctionKind functionType, std::string argsMessage, MPIInfo mpiInfo);

#endif /* ifndef CLOPENCV_H */

