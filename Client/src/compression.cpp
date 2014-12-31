/* zpipe.c: example of proper use of zlib's inflate() and deflate()
   Not copyrighted -- provided to the public domain
   Version 1.4  11 December 2005  Mark Adler */

/* Version history:
   1.0  30 Oct 2004  First version
   1.1   8 Nov 2004  Add void casting for unused return values
                     Use switch statement for inflate() return values
   1.2   9 Nov 2004  Add assertions to document zlib guarantees
   1.3   6 Apr 2005  Remove incorrect assertion in inf()
   1.4  11 Dec 2005  Add hack to avoid MSDOS end-of-line conversions
                     Avoid some compiler warnings for input and output buffers
 */

#include "compression.h"
#include "zlib.h"
#include "snappy-c.h"


/* report a zlib or i/o error */
int zerr(int ret)
{
    switch (ret) {
    case Z_ERRNO:
        printf("error reading or writing\n");
        break;
    case Z_STREAM_ERROR:
        printf("invalid compression level\n");
        break;
    case Z_DATA_ERROR:
        printf("invalid or incomplete deflate data\n");
        break;
    case Z_MEM_ERROR:
        printf("out of memory\n");
        break;
    case Z_VERSION_ERROR:
        printf("zlib version mismatch!\n");
    }
    return ret;
}

/* report a snappy error */
int serr(int ret)
{
    switch (ret) {
    case SNAPPY_OK:
	break;
    case SNAPPY_INVALID_INPUT:
	printf("Invalid input\n");
	break;
    case SNAPPY_BUFFER_TOO_SMALL:
	printf("Too small\n");
	break;
    }
    return ret;
}
  
int compressZlib( unsigned char * in, size_t sizeIn, unsigned char * out, size_t &sizeOut, int level){

    int ret, flush;
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    ret = deflateInit(&strm, level);
    if (ret != Z_OK)
        return ret;
    strm.avail_in =  sizeIn;
    flush = Z_FINISH ;
    strm.next_in = in;
    strm.avail_out = sizeIn;
    strm.next_out = out;
    ret = deflate(&strm, flush);    
    assert(ret != Z_STREAM_ERROR);  
    assert(strm.avail_in == 0);     
    sizeOut = sizeIn - strm.avail_out;
    (void)deflateEnd(&strm);
    return Z_OK;
}

int decompressZlib(unsigned char * in, size_t sizeIn, unsigned char * out, size_t sizeOut){

    int ret;
    z_stream strm;
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    ret = inflateInit(&strm);
    if (ret != Z_OK)
        return ret;
    strm.next_in = in;
    strm.avail_in = sizeIn;
    strm.avail_out = sizeOut;
    strm.next_out = out;
    ret = inflate(&strm, Z_NO_FLUSH);
    assert(ret != Z_STREAM_ERROR);  
    switch (ret) {
    case Z_NEED_DICT:
        ret = Z_DATA_ERROR;     
    case Z_DATA_ERROR:
    case Z_MEM_ERROR:
        (void)inflateEnd(&strm);
        return ret;
    }
    (void)inflateEnd(&strm);
    return Z_OK;
}

// The main compression method which is used for all different techniques
int compress(const unsigned char * in, size_t sizeIn, unsigned char * out, size_t &sizeOut, int level, enum cloudCompressionKind compressKind){
  int ret = 0;
  switch(compressKind){
  case NoCompression:
    printf("This should never happen\n");
    return 0;
  case ZlibCompression:
    return zerr(compressZlib((unsigned char *)in, sizeIn, out, sizeOut, level));
  case SnappyCompression:
    return serr(snappy_compress((const char *)in, sizeIn, (char *)out,  &sizeOut));
  }
  return ret;
}

// The main decompression method which is used for all different techniques
int decompress(const unsigned char * in, size_t sizeIn, unsigned char * out, size_t  &sizeOut, enum cloudCompressionKind compressKind){
  int ret = 0;
  switch(compressKind){
  case NoCompression:
    printf("This should never happen\n");
    return 0;
  case ZlibCompression:
    return zerr(decompressZlib((unsigned char *)in, sizeIn, out, sizeOut));
  case SnappyCompression:
    return serr(snappy_uncompress((const char *)in, sizeIn, (char *)out, &sizeOut));
  }
  return ret;
}

// Returns the maximum length of the compressed data for all different compression techniques
size_t getMaxLength(size_t sizeIn, enum cloudCompressionKind compressKind){
  switch(compressKind){
  case NoCompression:
    printf("This should never happen\n");
    return 0;
  case ZlibCompression:
    return sizeIn;
  //Snappy compressed data might have bigger size than the original data  
  case SnappyCompression:
    return snappy_max_compressed_length(sizeIn);
  }
  return 0;
}
