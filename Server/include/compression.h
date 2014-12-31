/*
 * $Id$
 */
#ifndef COMPRESSION_H
#  define COMPRESSION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
int compress (const unsigned char * in, size_t sizeIn, unsigned char * out, size_t &sizeOut, int level);
size_t getMaxLength( size_t sizeIn);
int decompress(const unsigned char * in, size_t sizeIn, unsigned char * out, size_t &sizeOut);

#endif /* ifndef COMPRESSION_H */

