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
#endif

static inline void subBytes(uint8_t *state)
{
    /* Perform the permutations */
    for(int i = 0; i < 16; i++)
        state[i] = state[i] ^ rotl8(state[i], 1) ^ rotl8(state[i], 2) ^ rotl8(state[i], 3) ^ rotl8(state[i], 4);
    return;
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

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
            astate[j][i] = rotState[i][j];
    }
    memcpy(state, astate, 16);
    return;
}

static inline void handleCounter(AES_Counter_t *counter, AES_Counter_t *dest, uint8_t *key)
{
    uint8_t state[4][4];
}
/* Encrypt a file */
void AES_enc_f(FILE *src, FILE *dest, AES_Counter_t *counter, uint8_t *key)
{
    int C;
    /* Copy file */
    while((C = fgetc(src)) != EOF)
        fputc(C, dest);

    /* Add padding */
    for(int i = 0; i < 16; i++)
        fputc(0, dest);

    while(ftell(src) % 16)
        fputc(0, dest);
    
    rewind(dest);
}

/* Encrypt some memory */
void AES_enc_m(void *src, void *dest, AES_Counter_t *counter, size_t size, uint8_t *key);

/* Encrypt a file */
void AES_dec_f(FILE *src, FILE *dest, AES_Counter_t *counter, uint8_t *key);

/* Encrypt some memory */
void AES_dec_m(void *src, void *dest, AES_Counter_t *counter, size_t size, uint8_t *key);