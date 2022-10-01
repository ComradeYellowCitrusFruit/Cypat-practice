#ifndef CRYPT_SHA256_H
#define CRYPT_SHA256_H

#include <stdio.h>

/*  Our implementation of SHA256, working on a buffer in memory, written in house because fuck it why not
*   @param *src Memory to hash
*   @param size Size of memory to hash
*   @param *destbuf Where to put the results, assumed to be already allocated
*/
void SHA256_M(void *src, size_t size, void *destbuf);

/*  Our implementation of SHA256, working on a file, written in house because fuck it why not
*   @param *file File to hash
*   @param *destbuf Where to put the results, assumed to be already allocated
*/
void SHA256_F(FILE *file, void *destbuf);

#endif