#include <utility>
#include "clopencv.h" 
#include "cloud.h" 
#include "clopencvargs.pb.h" 

using namespace clopencvargs;


cloudError_t cloudFaceTrain(TCPSocket & socketID, int rows, int cols, 
    char * images, int *  labels, double * eigenValues, double * eigenVectors, double * mean, double * projections) 
{
  std::string message;
  FaceTrainMessage faceMessage;
  faceMessage.set_rows(rows);
  faceMessage.set_cols(cols);
  faceMessage.set_images(reinterpret_cast<int64_t>(images));
  faceMessage.set_labels(reinterpret_cast<int64_t>(labels));
  faceMessage.set_eigenvalues(reinterpret_cast<int64_t>(eigenValues));
  faceMessage.set_eigenvectors(reinterpret_cast<int64_t>(eigenVectors));
  faceMessage.set_mean(reinterpret_cast<int64_t>(mean));
  faceMessage.set_projections(reinterpret_cast<int64_t>(projections));
  faceMessage.SerializeToString(&message);
  return cloudFunctionCall(socketID, ClOpenCVFaceTrain, message); 
}
