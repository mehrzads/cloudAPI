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
    PointerCommand,
    SizeCommand,
    CloseCommand
};

enum cloudCompressionKind{
    NoCompression,
    ZlibCompression,
    SnappyCompression
};
#endif /* ifndef COMMON_H */

