#ifndef CRYPT_RAND_H
#define CRYPT_RAND_H

#include <stdint.h>

/* Get a cryptographically secure random byte */
uint8_t getRandByte();
/* Get count number of cryptographically secure random bytes and place them at dest*/
void getRandBytes(void *dest, size_t count);

#endif