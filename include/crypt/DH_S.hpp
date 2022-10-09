#ifndef CRYPT_DIFFIE_HELLMAN_SECRET_HPP
#define CRYPT_DIFFIE_HELLMAN_SECRET_HPP

/* We're gonna have to get a solution for msvc users at some point, or cut out msvc, either way, we'll need to make a tough decision */
#include <gmp.h>
#include <gmpxx.h>

/* A header file for Diffie-Hellman internal functions. */

/* A simple union to allow us to access the inner structure of an mpz_class, in case we ever need to, perhaps to transmit it over the network. */
union MPZ
{
    /* Class version */
    mpz_class mpz_c;
    /* Struct version */
    mpz_t mpz_s;
};

extern MPZ modulus;

#endif