#include <utility>
#include <cblas.h>              /* Basic Linear Algebra I/O */
#include <math.h>              /* Basic Linear Algebra I/O */
#include "mpi.h"
#include "common.h" 
#include "clopencvargs.pb.h" 
#include "server.h"
#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;
using namespace clopencvargs;
using namespace cv;
FaceTrainMessage facetrainMessage;


cloudError_t cloudFaceTrain(int rows, int cols,
    char * images,
    int * labels,
    MPIInfo mpiInfo){
  Mat imagesMat(rows, cols, CV_64FC1, images);
  vector<Mat> imagesVec;
  for (int i = 0; i <rows; i++)
     imagesVec.push_back(imagesMat.row(i));
  Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
  vector<int> labelsVec(labels, labels + rows *sizeof(int));
  model->MPItrain(imagesVec, labelsVec);

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
