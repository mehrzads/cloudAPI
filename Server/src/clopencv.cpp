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
    MPIInfo mpiInfo){
  Mat imagesMat(rows, cols, 0, images);
  vector<Mat> imagesVec;
  vector<int> labelsVec;
  for (int i = 0; i <rows; i++){
     imagesVec.push_back(imagesMat.row(i));
     labelsVec.push_back(labels[i]);
  }

  for (int i = 0; i < 10; i++)
	printf("%d\t%d\t%d\t%d\t%d\n",labels[i], images[i], i, imagesMat.data[i], imagesVec[0].data[i]);

  printf("labels.size %d\t images total %d\t images elem %d\n", labelsVec.size(),  imagesMat.total() ,imagesMat.elemSize());

  Ptr<FaceRecognizer> model = createEigenFaceRecognizer();
//  vector<int> labelsVec(labels, labels + rows *sizeof(int));
  model->MPItrain(imagesVec, labelsVec);
  // Here is how to get the eigenvalues of this Eigenfaces model:
  Mat eigenValuesMat = model->getMat("eigenvalues");
  memcpy(eigenValues, eigenValuesMat.data, eigenValuesMat.total() * eigenValuesMat.elemSize());
  printf("EigenValues %dX%d %d %d\n", eigenvalues.rows, eigenvalues.cols, eigenvalues.elemSize(), eigenvalues.type()); 
  // And we can do the same to display the Eigenvectors (read Eigenfaces):
  Mat eigenVectorsMat = model->getMat("eigenvectors");
  memcpy(eigenVectors, eigenVectorsMat.data, eigenVectorsMat.total() * eigenVectorsMat.elemSize());
  printf("EigenVectors %dX%d %d %d\n", W.rows, W.cols, W.elemSize(), W.type()); 
  // Get the sample mean from the training data
  Mat meanMat = model->getMat("mean");
  memcpy(mean, meanMat.data, meanMat.total() * meanMat.elemSize());
  printf("mean %dX%d %d %d\n", mean.rows, mean.cols, mean.elemSize(), mean.type()); 

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
	    mpiInfo
	    );
       break;
    default:
       assert("Wrong Clblas FunctionType" && 0);
       break;
  }
  return CloudSuccess;
       
} 
