/*
 * $Id$
 */
#ifndef COMPRESSION_H
#  define COMPRESSION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "common.h"

int compress (const unsigned char * in, size_t sizeIn, unsigned char * out, size_t &sizeOut, int level, enum cloudCompressionKind compressKind);
size_t getMaxLength( size_t sizeIn, enum cloudCompressionKind compressKind);
int decompress(const unsigned char * in, size_t sizeIn, unsigned char * out, size_t &sizeOut, enum cloudCompressionKind compressKind);

#endif /* ifndef COMPRESSION_H */

