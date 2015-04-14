#include <utility>
#include "clopencv.h" 
#include "cloud.h" 
#include "clopencvargs.pb.h" 

using namespace clopencvargs;


cloudError_t cloudFaceTrain(TCPSocket & socketID, int rows, int cols, 
    char * images, int *  labels) 
{
  std::string message;
  FaceTrainMessage faceMessage;
  faceMessage.set_rows(rows);
  faceMessage.set_cols(cols);
  faceMessage.set_images(reinterpret_cast<int64_t>(images));
  faceMessage.set_labels(reinterpret_cast<int64_t>(labels));
  faceMessage.SerializeToString(&message);
  return cloudFunctionCall(socketID, ClOpenCVFaceTrain, message); 
}
