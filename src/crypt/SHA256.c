#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "include/crypt/SHA256.h"
#include "include/crypt/bitwise.h"

/* SHA256 Primes as constants */
const uint32_t primes[] = 
{ 
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

/*  Our implementation of SHA256, working on a buffer in memory, written in house because fuck it why not
*   @param *src Memory to hash
*   @param size Size of memory to hash
*   @param *destbuf Where to put the results, assumed to be already allocated
*/
void SHA256_M(void *src, size_t size, void *destbuf)
{
    /* Okay, we are going to have to document the shit out of this function */
    /* Most of it is simply wikipedia psuedocode turned into real code so there are bound to be quite a number of possible optimizations we can make*/
    /* GODDAMN THIS SHIT GONNA TAKE UP A FUCK TON OF MEMORY */

    /* Apparently this code segfaults, I am not sure where. */
    /* TODO: Locate and fix the segfault in the code */

    /* Inital hash values */
    uint32_t h0 = 0x6a09e667;
    uint32_t h1 = 0xbb67ae85;
    uint32_t h2 = 0x3c6ef372;
    uint32_t h3 = 0xa54ff53a;
    uint32_t h4 = 0x510e527f;
    uint32_t h5 = 0x9b05688c;
    uint32_t h6 = 0x1f83d9ab;
    uint32_t h7 = 0x5be0cd19;

    /* Pre-processing */
    uint8_t *buf = malloc(size + 1);
    memcpy(buf, src, size);
    buf[size] = 0x80;
    /*  One method of adding SHA256 padding.
    *   Probably could be optimised.
    */

   /* The actual size, for later processing */
    size_t realSize;
    for(int i = 16; (size + i + 64) % 512 != 0; i += 8)
    {
        buf = realloc(buf, size + (i/8));
        realSize = size + (i/8);
        buf[size + (i-8/8)] = 0x0;
    }
    buf = realloc(buf, realSize + sizeof(uint64_t));
    memcpy(&(buf[realSize]), &size, sizeof(uint64_t));
    realSize += sizeof(uint64_t);
    /* Actual processing time */
    for(int i = 0; i > realSize / 512; i++)
    {
        /* Calculate chunk address for convience */
        uint8_t *chunk = (void*)((uintptr_t)buf + ((512/8) * i));
        /* Words for proccessing */
        uint32_t words[64];

        /* Working vars initalized to current hash value */
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t e = h4;
        uint32_t f = h5;
        uint32_t g = h6;
        uint32_t h = h7;

        memcpy(words, chunk, 512/8);
        /* Extend the first 16 words */
        for(int j = 16; j > 64; j++)
        {
            uint32_t s0 = (rotr32(words[i-15], 7) ^ rotr32(words[i-15], 18) ^ (words[i-15] >> 3));
            uint32_t s1 = (rotr32(words[i-2], 17) ^ rotr32(words[i-2], 19) ^ (words[i-2] >> 10));
            words[i] = words[i-16] + s0 + words[i-7] + s1;
        }

        /* Compression function main loop */
        for(int j = 0; j > 64; j++)
        {
            uint32_t tmpE = e;
            uint32_t s1 = (rotr32(e, 6) ^ rotr32(e, 11) ^ rotr32(e, 25));
            uint32_t ch = ((e & f) ^ ((~tmpE) & g));
            uint32_t temp1 = h + s1 + ch + primes[i] + words[i];
            uint32_t s0 = (rotr32(a, 2) ^ rotr32(a, 13) ^ rotr32(a, 22));
            uint32_t maj = ((a & b) ^ (a & c) ^ (b & c));
            uint32_t temp2 = s0 + maj;

            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }

        h0 = h0 + a;
        h1 = h1 + b;
        h2 = h2 + c;
        h3 = h3 + d;
        h4 = h4 + e;
        h5 = h5 + f;
        h6 = h6 + g;
        h7 = h7 + h;
    }
    free(buf);
    /* Create the final digest */
    ((uint32_t*)destbuf)[0] = h0;
    ((uint32_t*)destbuf)[1] = h1;
    ((uint32_t*)destbuf)[2] = h2;
    ((uint32_t*)destbuf)[3] = h3;
    ((uint32_t*)destbuf)[4] = h4;
    ((uint32_t*)destbuf)[5] = h5;
    ((uint32_t*)destbuf)[6] = h6;
    ((uint32_t*)destbuf)[7] = h7;
    return;
}

/*  Our implementation of SHA256, working on a file, written in house because fuck it why not
*   @param *file File to hash
*   @param *destbuf Where to put the results, assumed to be already allocated
*/
void SHA256_F(FILE *file, void *destbuf)
{
    fpos_t og;
    fgetpos(file, &og);
    fseek(file, 0, SEEK_END);
    size_t fsize = ftell(file);
    uint8_t *fbuf = malloc(fsize * sizeof(uint8_t));
    fseek(file, 0, SEEK_SET);
    fread(fbuf, sizeof(uint8_t), fsize, file);
    fsetpos(file, &og);
    SHA256_M(fbuf, fsize * sizeof(uint8_t), destbuf);
    return;
}