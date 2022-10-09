/* We're gonna have to get a solution for msvc users at some point, or cut out msvc, either way, we'll need to make a tough decision */
#include <gmp.h>
#include <gmpxx.h>

#include "include/crypt/DH_S.hpp"

/* Since this header automatically handles extern "c" for function declarations, it is safe to not use extern "C" on this header */
#include "include/crypt/DH.h"

/* Generate a valid secret int */
C void genSecret(void *secret)
{
}

/* Combine base and secret and place them in dest */
C void handleSecret(void *secret, void *dest)
{
    MPZ *Msecret = secret;
    MPZ *Mdest = dest;
    MPZ gen;
    gen.mpz_c = RFC_GENERATOR;
    /* How nice of the GNU people to make one function for this */
    mpz_powm_sec(Mdest->mpz_s, gen.mpz_s, Msecret->mpz_s, modulus.mpz_s);
}
