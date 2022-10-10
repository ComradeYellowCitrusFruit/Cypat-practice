/*
*
*   include/crypt/DH.h
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

#ifndef CRYPT_DIFFIE_HELLMAN_H
#define CRYPT_DIFFIE_HELLMAN_H

#ifdef __cplusplus
#define C extern "C"
#else
#define C extern
#endif

/* Literally everything derived from RFC comes from here: https://www.rfc-editor.org/rfc/rfc3526 */
/* We will be using a 2048 bit key for everything, using SHA for further key derivation */

#include <stdint.h>

#define DH_MODULUS_BITS 2048
#define DH_EXPONENT_BITS 512

/* RFC 2048 bit prime number as a uint32_t array, unnecessary for now. */
/* C uint32_t RFC_prime[64]; */

/* RFC 2048 bit prime number as a base62 string, for use with GMP */
C char RFC_prime_b62str[345];

#define RFC_GENERATOR 2

/* Initiate Diffie-Hellman shit */
C void initDH();

/*  Get a pointer to a valid GMP++ class allocated with malloc, don't fuck with these */
C void *getPtr();

/* Generate a valid secret int */
C void genSecret(void *secret);

/* Combine base and secret and place them in dest */
C void handleSecret(void *secret, void *dest);

#endif