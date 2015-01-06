/*
 * $Id$
 */
#ifndef CLBLAS_H
#  define CLBLAS_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

cloudError_t matrixMultiply(int l, int m, int n , float * A, float * B, float *C);
cloudError_t handleClblasFunction(cloudFunctionKind functionType, std::string argsMessage);

#endif /* ifndef CLBLAS_H */

