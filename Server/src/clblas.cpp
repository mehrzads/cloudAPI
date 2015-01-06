#include <utility>
#include "common.h" 
#include "clblas.h" 
#include "clblasargs.pb.h" 

using namespace clblasargs;
MatrixMultiplicationMessage matrixMultiplicationArgsMessage;
cloudError_t matrixMultiply(int l, int m, int n , float * A, float * B, float *C){
  for (int i = 0 ; i < l ; i++)
    for (int j = 0; j < n; j++) {
      float sum = 0;
      for (int k = 0; k < m; k++)
	sum = A[i * m + k] * B[k * n + j];
      C[i * n + j] = sum;
    }
  return CloudSuccess; 
}

cloudError_t handleClblasFunction(cloudFunctionKind functionType, std::string argsMessage)
{
  switch (functionType){
    case ClBlasMatrixMaltiplication:
       matrixMultiplicationArgsMessage.ParseFromString(argsMessage);
       matrixMultiply(matrixMultiplicationArgsMessage.dim0(),
	   matrixMultiplicationArgsMessage.dim1(),
	   matrixMultiplicationArgsMessage.dim2(),
	   reinterpret_cast<float *>(matrixMultiplicationArgsMessage.matrix0()),
	   reinterpret_cast<float *>(matrixMultiplicationArgsMessage.matrix1()),
	   reinterpret_cast<float *>(matrixMultiplicationArgsMessage.matrix2()));
       break;
    default:
       assert("Wrong Clblas FunctionType" && 0);
       break;
  }
  return CloudSuccess;
       
} 
