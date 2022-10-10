/*
*
*   include/crypt/SHA256.h
*   Originally written by Alicia Antó Valencía - https://github.com/ComradeYellowCitrusFruit
*
*   Cyber Competition Suite - A collection of programs for cybersecurity competitions and practices
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