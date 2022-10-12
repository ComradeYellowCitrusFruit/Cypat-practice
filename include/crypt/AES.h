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
#include <stdbool.h>

/* Generate a counter, for our purposes */
void genCounter(void *buf);

/* Encrypt a file */
void AES_f(FILE *src, FILE *dest, uint8_t *key);

/* Encrypt some memory */
void AES_m(void *src, uint8_t *dest, size_t size, uint8_t *key);

#endif