#include <utility>
#include <cblas.h>              /* Basic Linear Algebra I/O */
#include "common.h" 
#include "clblas.h" 
#include "clblasargs.pb.h" 

using namespace clblasargs;
DGEMMMessage dgemmMessage;
CBLAS_ORDER OrderTransTable[]={CblasRowMajor, CblasColMajor};
CBLAS_TRANSPOSE TransposeTransTable[]={CblasNoTrans, CblasTrans, CblasConjTrans};



cloudError_t cloudDgemm(CLBLAS_ORDER Order, CLBLAS_TRANSPOSE TRANSA, CLBLAS_TRANSPOSE TRANSB, 
    int M, int N, int K, 
    double ALPHA, 
    double * A, int LDA, 
    double * B, int LDB, 
    double BETA, 
    double * C, int LDC){
  cblas_dgemm(OrderTransTable[Order], TransposeTransTable[CblasNoTrans], TransposeTransTable[CblasNoTrans], M,    N,    K, ALPHA,   A,   LDA, B, LDB, BETA, C,  LDC);
  return CloudSuccess; 
}
cloudError_t handleClblasFunction(cloudFunctionKind functionType, std::string argsMessage)
{
  switch (functionType){
    case ClBlasDGEMM:
       dgemmMessage.ParseFromString(argsMessage);
       cloudDgemm(static_cast<CLBLAS_ORDER>(dgemmMessage.order()),
            static_cast<CLBLAS_TRANSPOSE>(dgemmMessage.transa()),
            static_cast<CLBLAS_TRANSPOSE>(dgemmMessage.transb()),
            dgemmMessage.m(),
            dgemmMessage.n(),
            dgemmMessage.k(),
            dgemmMessage.alpha(),
            reinterpret_cast<double *>(dgemmMessage.a()), dgemmMessage.lda(),
            reinterpret_cast<double *>(dgemmMessage.b()), dgemmMessage.ldb(),
            dgemmMessage.beta(),
            reinterpret_cast<double *>(dgemmMessage.c()), dgemmMessage.ldc());
       break;
    default:
       assert("Wrong Clblas FunctionType" && 0);
       break;
  }
  return CloudSuccess;
       
} 
