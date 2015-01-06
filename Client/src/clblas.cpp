#include <utility>
#include "common.h" 
#include "clblas.h" 
#include "cloud.h" 
#include "clblasargs.pb.h" 

using namespace clblasargs;

cloudError_t matrixMultiply(int socketID, int l, int m, int n , float * A, float * B, float *C){
  std::string message;
  MatrixMultiplicationMessage matrixMultiplicationMessage;
  matrixMultiplicationMessage.set_dim0(l);
  matrixMultiplicationMessage.set_dim1(m);
  matrixMultiplicationMessage.set_dim2(n);
  matrixMultiplicationMessage.set_matrix0(reinterpret_cast<int64_t>(A));
  matrixMultiplicationMessage.set_matrix1(reinterpret_cast<int64_t>(B));
  matrixMultiplicationMessage.set_matrix2(reinterpret_cast<int64_t>(C));
  matrixMultiplicationMessage.SerializeToString(&message);
  return cloudFunctionCall(socketID, ClBlasMatrixMaltiplication, message); 
}
