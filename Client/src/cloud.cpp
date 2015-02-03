#include "cloud.h"
#include "cloudmessage.pb.h"
using namespace std;
using namespace cloudmessaging;

PointerMessage pointerMessage;
SizeMessage sizeMessage;
TransferMessage transferMessage;
FunctionCallMessage functionCallMessage;
string message;

// Initializing the connection
cloudError_t  cloudInit(int portno, char * hostname, TCPSocket  &tcpSocket)
{
  tcpSocket.setnThreads(N_TCP_THREADS);
  return tcpSocket.clientConnect(portno, hostname);
}


// Calling a library function
cloudError_t  cloudFunctionCall(TCPSocket  &tcpSocket, cloudFunctionKind functionType, std::string argsMessage)
{
  functionCallMessage.set_messagetype(FunctionCallCommand);
  functionCallMessage.set_functiontype(functionType);
  functionCallMessage.SerializeToString(&message);
  tcpSocket.sendMessage(message);
  tcpSocket.sendMessage(argsMessage);
  return CloudSuccess;
	
}


// Allocating an array with size in the server.
cloudError_t cloudMalloc(TCPSocket  &tcpSocket, void ** cloudPtr, size_t size)
{
  sizeMessage.set_messagetype(AllocCommand);
  sizeMessage.set_size(size);
  sizeMessage.SerializeToString(&message);
  tcpSocket.sendMessage(message);
  tcpSocket.recMessage(message);
  pointerMessage.ParseFromString(message);
  *cloudPtr =  reinterpret_cast<void *> (pointerMessage.pointer());
  return CloudSuccess;
}


// cloudMemcpy is transferring data between client and the server
cloudError_t cloudMemcpy(TCPSocket  &tcpSocket,  void *  dst,  void *  src,  size_t  count,   enum cloudMemcpyKind   directionKind, enum cloudCompressionKind compressKind)
{
  if (compressKind != NoCompression)
  {
    if (directionKind == cloudMemcpyClientToCloud)
    {
      size_t compressedSize= getMaxLength( count, compressKind);
      unsigned char * out  = static_cast<unsigned char *>(malloc(compressedSize));
      compress(static_cast<const unsigned char *>(src), count, out, compressedSize, 1, compressKind);

      transferMessage.set_messagetype(GetCommand);
      transferMessage.set_compresskind(compressKind);
      transferMessage.set_size(count);
      transferMessage.set_compressedsize(compressedSize);
      transferMessage.set_pointer(reinterpret_cast<int64_t>(dst));
      transferMessage.SerializeToString(&message);

      tcpSocket.sendMessage(message);
      tcpSocket.sendData(out, compressedSize);
      free(out);
    }
    else if (directionKind == cloudMemcpyCloudToClient)
    {
      transferMessage.set_messagetype(SendCommand);
      transferMessage.set_compresskind(compressKind);
      transferMessage.set_size(count);
      transferMessage.set_compressedsize(0);
      transferMessage.set_pointer(reinterpret_cast<int64_t>(src));
      transferMessage.SerializeToString(&message);

      tcpSocket.sendMessage(message);
      tcpSocket.recMessage(message);

      sizeMessage.ParseFromString(message);
      size_t compressedSize =  static_cast<size_t>(sizeMessage.size());
      unsigned char * out  = static_cast<unsigned char *>(malloc(compressedSize * sizeof(char)));
      tcpSocket.recData(out, compressedSize);
      decompress(out, compressedSize, static_cast<unsigned char *>(dst), count, compressKind);
      free(out);
    }
  }
  else
  {
    if (directionKind == cloudMemcpyClientToCloud)
    {
      transferMessage.set_messagetype(GetCommand);
      transferMessage.set_compresskind(NoCompression);
      transferMessage.set_size(count);
      transferMessage.set_compressedsize(0);
      transferMessage.set_pointer(reinterpret_cast<int64_t>(dst));
      transferMessage.SerializeToString(&message);
      tcpSocket.sendMessage(message);
      tcpSocket.sendData(src, count);
    }
    else if (directionKind == cloudMemcpyCloudToClient)
    {
      transferMessage.set_messagetype(SendCommand);
      transferMessage.set_compresskind(NoCompression);
      transferMessage.set_size(count);
      transferMessage.set_compressedsize(0);
      transferMessage.set_pointer(reinterpret_cast<int64_t>(src));
      transferMessage.SerializeToString(&message);
      tcpSocket.sendMessage(message);
      tcpSocket.recData(dst, count);
    }
  }
  return CloudSuccess;
}


// Freeing the array on the cloud
cloudError_t cloudFree(TCPSocket  & tcpSocket, void * cloudPtr)
{
  pointerMessage.set_messagetype(FreeCommand);
  pointerMessage.set_pointer(reinterpret_cast<int64_t>(cloudPtr));
  pointerMessage.SerializeToString(&message);
  return tcpSocket.sendMessage(message);
}


// Finishing the connection
cloudError_t cloudFinish(TCPSocket  & tcpSocket)
{
  sizeMessage.set_messagetype(CloseCommand);
  sizeMessage.set_size(0);
  sizeMessage.SerializeToString(&message);
  tcpSocket.sendMessage(message);
  tcpSocket.closeSocket();
  return CloudSuccess;
}
