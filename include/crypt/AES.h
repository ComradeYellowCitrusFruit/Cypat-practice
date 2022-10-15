/*
*
*   include/crypt/AES.h
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

#ifndef CRYPT_AES_H
#define CRYPT_AES_H

/* Our implementation of AES-256, using counter mode */

#include <stdio.h>
#include <stdint.h>

typedef struct
{
    uint64_t IV;
    uint64_t counter;
} AES_Counter_t;

/* Generate a counter, for our purposes */
void genCounter(AES_Counter_t *buf);

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
void AES_f(FILE *src, FILE *dest, AES_Counter_t *counter, uint8_t *key);

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
void AES_m(void *src, void *dest, AES_Counter_t *counter, size_t size, uint8_t *key);

#endif