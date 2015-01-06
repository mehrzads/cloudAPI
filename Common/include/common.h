/*
 * $Id$
 */
#ifndef COMMON_H
#  define COMMON_H
enum cloudMemcpyKind{
   cloudMemcpyClientToCloud,
   cloudMemcpyCloudToClient
 };

enum cloudError_t{
    CloudSuccess,
    CloudErrorRead,
    CloudErrorWrite,
    CloudErrorConnection,
    CloudErrorOpen,
    CloudErrorNoHost
} ;

enum cloudCommandKind{
    AllocCommand,
    GetCommand,
    SendCommand,
    FreeCommand,
    FunctionCallCommand,
    PointerCommand,
    SizeCommand,
    CloseCommand
};

enum cloudCompressionKind{
    NoCompression,
    ZlibCompression,
    SnappyCompression
};

enum cloudFunctionKind{
    ClBlasStart = 0,
    ClBlasMatrixMaltiplication,
    ClBlasEnd
};
#endif /* ifndef COMMON_H */

