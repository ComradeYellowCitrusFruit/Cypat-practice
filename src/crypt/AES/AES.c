/*
*
*   src/crypt/AES/AES.c
*   Originally written by Alicia Antó Valencía - https://github.com/ComradeYellowCitrusFruit
*
*   A collection of programs for cybersecurity competitions and practices
*   Copyright (C) 2022  Alicia Antó Valencía
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "include/crypt/bitwise.h"
#include "include/crypt/AES.h"

#ifdef __x86_64__
/* We'd be idiots not to make use of the x64 AES extentions, this function handles that, it is written in a seperate assembly language file */
__attribute__((sysv_abi)) extern void AES_ASM(void *state, void *expandedKey) asm("AES");
/* Returns one if true, zero if false */
extern int supportsAESExtentions() asm("SUPPORTS_AES");
#endif

static inline void subBytes(uint8_t *state)
{
    /* Perform the permutations */
    for(int i = 0; i < 16; i++)
        state[i] = state[i] ^ rotl8(state[i], 1) ^ rotl8(state[i], 2) ^ rotl8(state[i], 3) ^ rotl8(state[i], 4);
    return;
}

static inline uint32_t subWord(uint32_t word)
{
    uint8_t *ptr = &word;
    ptr[0] = ptr[0] ^ rotl8(ptr[0], 1) ^ rotl8(ptr[0], 2) ^ rotl8(ptr[0], 3) ^ rotl8(ptr[0], 4);
    ptr[1] = ptr[1] ^ rotl8(ptr[1], 1) ^ rotl8(ptr[1], 2) ^ rotl8(ptr[1], 3) ^ rotl8(ptr[1], 4);
    ptr[2] = ptr[2] ^ rotl8(ptr[2], 1) ^ rotl8(ptr[2], 2) ^ rotl8(ptr[2], 3) ^ rotl8(ptr[2], 4);
    ptr[3] = ptr[3] ^ rotl8(ptr[3], 1) ^ rotl8(ptr[3], 2) ^ rotl8(ptr[3], 3) ^ rotl8(ptr[3], 4);
    return word;
}

static inline void shiftRows(uint8_t *state)
{
    uint8_t astate[4][4];
    uint8_t tmpstate[4][4];
    memcpy(astate, state, 16);
    memcpy(tmpstate, state, 16);

    /* I thank God every day for the modulus operator */
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
            tmpstate[i][(j + i) % 4] = astate[i][j];
    }

    memcpy(state, tmpstate, 16);
    return;
}

/* Some code I copied from wikipedia */
static inline void gmix_column(unsigned char *r) {
    unsigned char a[4];
    unsigned char b[4];
    unsigned char c;
    unsigned char h;
    /* The array 'a' is simply a copy of the input array 'r'
     * The array 'b' is each element of the array 'a' multiplied by 2
     * in Rijndael's Galois field
     * a[n] ^ b[n] is element n multiplied by 3 in Rijndael's Galois field */ 
    for (c = 0; c < 4; c++) {
        a[c] = r[c];
        /* h is 0xff if the high bit of r[c] is set, 0 otherwise */
        h = (r[c] >> 7) & 1; /* arithmetic right shift, thus shifting in either zeros or ones */
        b[c] = r[c] << 1; /* implicitly removes high bit because b[c] is an 8-bit char, so we xor by 0x1b and not 0x11b in the next line */
        b[c] ^= h * 0x1B; /* Rijndael's Galois field */
    }
    r[0] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1]; /* 2 * a0 + a3 + a2 + 3 * a1 */
    r[1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2]; /* 2 * a1 + a0 + a3 + 3 * a2 */
    r[2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3]; /* 2 * a2 + a1 + a0 + 3 * a3 */
    r[3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0]; /* 2 * a3 + a2 + a1 + 3 * a0 */
}

static inline void mixColumns(uint8_t *state)
{
    uint8_t astate[4][4];
    uint8_t rotState[4][4];
    memcpy(astate, state, 16);

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
            rotState[j][i] = astate[i][j];
    }

    gmix_column(&(rotState[0][0]));
    gmix_column(&(rotState[1][0]));
    gmix_column(&(rotState[2][0]));
    gmix_column(&(rotState[3][0]));

    /* Rotate back to the original position */
    for(int k = 0; k < 3; k++)
    {
        for(int i = 0; i < 4; i++)
        {
            for(int j = 0; j < 4; j++)
                astate[j][i] = rotState[i][j];
        }
    }

    memcpy(state, astate, 16);
    return;
}

static inline uint8_t rcon(int i)
{
    uint8_t vals[] = { 1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36 };
    i--;
    
    /* I think thats how this works, I'm not sure */
    return vals[i % 10];
}

static inline void keySchedule(uint8_t *key, uint8_t *destKey)
{
    uint32_t *k = key;
    uint32_t *words = destKey;
    for(int i = 0; i < 120; i++)
    {
        if(i < 8)
            words[i] = k[i];
        else if(i >= 8 && (i % 8 == 0 % 8))
            words[i] = words[i-8] ^ subWord(rotl32(words[i-1], 8)) ^ (rcon(i/8) << 24);
        else if(i >= 8 && (i % 8 == 4 % 8))
            words[i] = words[i-8] ^ subWord(words[i-1]);
        else
            words[i] = words[i-8] ^ words[i-1];
    }
    return;
}

static inline void handleCounter(AES_Counter_t *counter, AES_Counter_t *dest, uint8_t *key)
{
    uint8_t state[16];
    memcpy(state, counter, 16);
    uint8_t *keys = malloc(120 * sizeof(uint32_t));

    /* Perform key expansion */
    keySchedule(key, keys);

    #ifdef __x86_64__
        /* Quick and easy harmless optimization */
        static int aesOpcodes = supportsAESExtentions();
        if(aesOpcodes == 1)
            /* Our optimizations in action */
            AES_ASM(state, keys);
        else
        {
            /* They don't support AES instructions */

            /* Offset for which key to use */
            int offset = 0;
            /* First round */
            for(int i = 0; i < 16; i++)
                state[i] ^= keys[i];
            
            offset += 16;

            /* Every other round except the last */
            for(int k = 0; k < 13; k++)
            {
                /* Perform all the AES functions */
                subBytes(state);
                shiftRows(state);
                mixColumns(state);
                /* AddRoundKey, since it's just a simple for loop, it isn't it's own function */
                for(int i = 0; i < 16; i++)
                    state[i] ^= keys[i + offset];
                offset += 16;
            }

            /* Last round */
            subBytes(state);
            shiftRows(state);
            for(int i = 0; i < 16; i++)
                state[i] ^= keys[i + offset];
        }
    #else

    /* Not x64 */

    /* Offset for which key to use */
    int offset = 0;
    /* First round */
    for(int i = 0; i < 16; i++)
        state[i] ^= keys[i];
            
    offset += 16;

    /* Every other round except the last */
    for(int k = 0; k < 13; k++)
    {
        /* Perform all the AES functions */
        subBytes(state);
        shiftRows(state);
        mixColumns(state);
        /* AddRoundKey, since it's just a simple for loop, it isn't it's own function */
        for(int i = 0; i < 16; i++)
            state[i] ^= keys[i + offset];
        offset += 16;
    }

    /* Last round */
    subBytes(state);
    shiftRows(state);
    for(int i = 0; i < 16; i++)
        state[i] ^= keys[i + offset];
    #endif

    free(keys);
    /* Transfer our state to dest */
    memcpy(state, dest, 16);
    return;
}

/*  Encrypt or decrypt a file.
*   The function will in theory work the same if src and dest are the same file with different pointers,
*   since the position of each is modified, 
*   data from src is only read from once, 
*   and data from dest is only written once.
*   The position of both files is restored at the end of the function
*   @param *src The source file, considered read only.
*   @param *dest The destination file, considered read-write, and is where the encrypted data is written.
*   @param *counter The counter, considered read-write and is treated as volatile, and is modified.
*   @param *key The key, considered read only.
*/
void AES_f(FILE *src, FILE *dest, AES_Counter_t *counter, uint8_t *key)
{   
    /* Save the file positions */
    fpos_t srcpos;
    fpos_t destpos;
    fgetpos(src, &srcpos);
    fgetpos(dest, &destpos);

    /* Rewind both files */
    rewind(src);
    rewind(dest);

    int C;
    /* Number of bytes we've processed, also the byte we're currently proccessing */
    int cc = 0;
    AES_Counter_t tmpC;
    uint8_t *counterBuf = &tmpC;
    /* Set it to negative one, so that the counter is accurate to the number of counters we've gone through */
    counter->counter = (uint64_t)-1;
    while((C = fgetc(src)) != EOF)
    {
        /* If we need to increment the counter or not */
        if(cc % 16 == 0)
        {
            counter->counter++;
            handleCounter(counter, &tmpC, key);
        }
        fputc(C ^ counterBuf[cc % 16], dest);
        cc++;
    }

    /* Restore the file positions */
    fsetpos(src, &srcpos);
    fsetpos(dest, &destpos);

    return;
}

/*  Encrypt or decrypt some memory.
*   The function will still work if *src and *dest are the same, 
*   as data from *src is only read from once, 
*   and data from *dest is only written once.
*   @param *src The source buffer, considered read only.
*   @param *dest The destination buffer, considered read-write, and is where the encrypted data is written.
*   @param *counter The counter, considered read-write and is treated as volatile, and is modified.
*   @param size The size of the two buffers.
*   @param *key The key, considered read only.
*/
void AES_m(void *src, void *dest, AES_Counter_t *counter, size_t size, uint8_t *key)
{
    /* Practically identical to AES_enc_f(), except with memory IO instead of file IO, unlike SHA256 */
    uint8_t *srcbuf = src;
    uint8_t *destbuf = dest;
    AES_Counter_t tmpC;
    uint8_t *counterBuf = &tmpC;
    for(int i = 0; i < size; i++)
    {
        if(i % 16 == 0)
        {
            counter->counter++;
            handleCounter(counter, &tmpC, key);
        }
        destbuf[i] = srcbuf[i] ^ counterBuf[i % 16];
    }

    return;
}