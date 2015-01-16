/*
 * $Id$
 */
#ifndef CLBLAS_H
#  define CLBLAS_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>

cloudError_t cloudDgemm(CLBLAS_ORDER Order, CLBLAS_TRANSPOSE TRANSA, CLBLAS_TRANSPOSE TRANSB, 
    int M, int N, int K, 
    double ALPHA, 
    double * A, int LDA, 
    double * B, int LDB, 
    double BETA, 
    double * C, int LDC);

cloudError_t handleClblasFunction(cloudFunctionKind functionType, std::string argsMessage);

#endif /* ifndef CLBLAS_H */

