/*
 * $Id$
 */
#ifndef CLBLAS_H
#  define CLBLAS_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

cloudError_t matrixMultiply(int socketID, int l, int m, int n , float * A, float * B, float *C);

#endif /* ifndef CLBLAS_H */

