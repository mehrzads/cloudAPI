/*
 * $Id$
 */
#ifndef CLBLAS_H
#  define CLBLAS_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "common.h"


cloudError_t cloudDgemm(int socketID, 
    CLBLAS_ORDER Order, 
    CLBLAS_TRANSPOSE TRANSA,  
    CLBLAS_TRANSPOSE TRANSB, 
    int M, int N, int K, 
    double ALPHA, 
    double * A, int LDA, 
    double * B, int LDB, 
    double BETA, 
    double * C, int LDC);

#endif /* ifndef CLBLAS_H */

