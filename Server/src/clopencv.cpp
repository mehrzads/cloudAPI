#include <utility>
#include <cblas.h>              /* Basic Linear Algebra I/O */
#include <math.h>              /* Basic Linear Algebra I/O */
#include "mpi.h"
#include "common.h" 
#include "clopencvargs.pb.h" 
#include "server.h"

using namespace std;
using namespace clopencvargs;
FaceTrainMessage facetrainMessage;


cloudError_t cloudFaceTrain(int rows, int cols,
    char * images,
    int * labels,
    MPIInfo mpiInfo){
  printf("cloud Face Train is called\n");
  return CloudSuccess; 
}
cloudError_t handleClOpenCVFunction(cloudFunctionKind functionType, std::string argsMessage, MPIInfo mpiInfo)
{
  switch (functionType){
    case ClOpenCVFaceTrain:
       facetrainMessage.ParseFromString(argsMessage);
       cloudFaceTrain(facetrainMessage.rows(),
            facetrainMessage.cols(),
            reinterpret_cast<char *>(facetrainMessage.labels()),
            reinterpret_cast<int *>(facetrainMessage.images()),
	    mpiInfo
	    );
       break;
    default:
       assert("Wrong Clblas FunctionType" && 0);
       break;
  }
  return CloudSuccess;
       
} 
