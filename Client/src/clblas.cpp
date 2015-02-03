#include <utility>
#include "clblas.h" 
#include "cloud.h" 
#include "clblasargs.pb.h" 

using namespace clblasargs;


cloudError_t cloudDgemm(TCPSocket & socketID, CLBLAS_ORDER Order, CLBLAS_TRANSPOSE TRANSA, CLBLAS_TRANSPOSE TRANSB, 
    int M, int N, int K, 
    double ALPHA, 
    double * A, int LDA, 
    double * B, int LDB, 
    double BETA, 
    double * C, int LDC)
{
  std::string message;
  DGEMMMessage dgemmMessage;
  dgemmMessage.set_order(Order);
  dgemmMessage.set_transa(TRANSA);
  dgemmMessage.set_transb(TRANSB);
  dgemmMessage.set_m(M);
  dgemmMessage.set_n(N);
  dgemmMessage.set_k(K);
  dgemmMessage.set_alpha(ALPHA);
  dgemmMessage.set_a(reinterpret_cast<int64_t>(A));
  dgemmMessage.set_lda(LDA);
  dgemmMessage.set_b(reinterpret_cast<int64_t>(B));
  dgemmMessage.set_ldb(LDB);
  dgemmMessage.set_beta(BETA);
  dgemmMessage.set_c(reinterpret_cast<int64_t>(C));
  dgemmMessage.set_ldc(LDC);
  dgemmMessage.SerializeToString(&message);
  return cloudFunctionCall(socketID, ClBlasDGEMM, message); 
}
