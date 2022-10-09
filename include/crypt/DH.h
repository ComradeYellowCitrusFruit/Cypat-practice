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