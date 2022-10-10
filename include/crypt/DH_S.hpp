/*
*
*   include/crypt/DH_S.hpp  
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