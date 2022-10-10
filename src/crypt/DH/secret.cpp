/*
*
*   src/crypt/DH/secret.cpp  
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

/* We're gonna have to get a solution for msvc users at some point, or cut out msvc, either way, we'll need to make a tough decision */
#include <gmp.h>
#include <gmpxx.h>

#include "include/crypt/DH_S.hpp"

/* Since this header automatically handles extern "c" for function declarations, it is safe to not use extern "C" on this header */
#include "include/crypt/DH.h"
C
{
    #include "include/crypt/rand.h"
}

/* Generate a valid secret int */
C void genSecret(void *secret)
{
    MPZ *Msecret;
    /* Set it to be null, just to be safe. */
    Msecret->mpz_c = 0;
    /* Fill the number with random data, this method also works to fill it with any data to big to fit in a smaller int, in case we need to */
    for(size_t i = 0; i < DH_EXPONENT_BITS/8; i++)
        Msecret->mpz_c = (Msecret->mpz_c << (i * 8)) | getRandByte();
    return;
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
    return;
}
