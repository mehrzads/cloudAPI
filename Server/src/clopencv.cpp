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
    double * eigenValues, 
    double * eigenVectors, 
    double * mean,
    double * projections,
    MPIInfo mpiInfo){
  Mat imagesMat(rows, cols, 0, images);
  vector<Mat> imagesVec;
  vector<int> labelsVec;
  for (int i = 0; i <rows; i++){
     imagesVec.push_back(imagesMat.row(i));
     labelsVec.push_back(labels[i]);
  }


  Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
//  vector<int> labelsVec(labels, labels + rows *sizeof(int));
  model->MPItrain(imagesVec, labelsVec);
  // Here is how to get the eigenvalues of this Eigenfaces model:
  Mat eigenValuesMat = model->getMat("eigenvalues");
  memcpy(eigenValues, reinterpret_cast<double *>(eigenValuesMat.data), eigenValuesMat.total() * eigenValuesMat.elemSize());
  // And we can do the same to display the Eigenvectors (read Eigenfaces):
  Mat eigenVectorsMat = model->getMat("eigenvectors");
  memcpy(eigenVectors, reinterpret_cast<double *>(eigenVectorsMat.data), eigenVectorsMat.total() * eigenVectorsMat.elemSize());
  // Get the sample mean from the training data
  Mat meanMat = model->getMat("mean");
  memcpy(mean, reinterpret_cast<double *>(meanMat.data), meanMat.total() * meanMat.elemSize());

  vector<Mat> projectionsVec = model->getMatVector("projections");
  Mat projectionsMat = model->asFaceRowMatrix(projectionsVec, CV_64FC1);
  memcpy(projections, reinterpret_cast<double *>(projectionsMat.data), projectionsMat.total() * projectionsMat.elemSize());
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
            reinterpret_cast<char *>(facetrainMessage.images()),
            reinterpret_cast<int *>(facetrainMessage.labels()),
            reinterpret_cast<double *>(facetrainMessage.eigenvalues()),
            reinterpret_cast<double *>(facetrainMessage.eigenvectors()),
            reinterpret_cast<double *>(facetrainMessage.mean()),
            reinterpret_cast<double *>(facetrainMessage.projections()),
	    mpiInfo
	    );
       break;
    default:
       assert("Wrong Clblas FunctionType" && 0);
       break;
  }
  return CloudSuccess;
       
} 
