#ifndef CRYPT_DIFFIE_HELLMAN_SECRET_HPP
#define CRYPT_DIFFIE_HELLMAN_SECRET_HPP

/* We're gonna have to get a solution for msvc users at some point, or cut out msvc, either way, we'll need to make a tough decision */
#include <gmp.h>
#include <gmpxx.h>

/* A header file for Diffie-Hellman internal functions. */

/*  A simple union to allow us to use an mpz_class as an mpz_t.
*   This works because an mpz_class is equal in memory to an mpz_t. 
*/
union MPZ
{
    /* Class version */
    mpz_class mpz_c;
    /* Struct version */
    mpz_t mpz_s;
};

extern MPZ modulus;

#endif