/*
*
*   src/crypt/DH/init.cpp  
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

/* We're gonna have to get a solution for msvc users at some point, or cut out msvc, either way, we'll need to make a tough decision */
#include <gmp.h>
#include <gmpxx.h>

#include "include/crypt/DH_S.hpp"

/* Since this header automatically handles extern "c" for function declarations, it is safe to not use extern "C" on this header */
#include "include/crypt/DH.h"

/* RFC 2048 bit prime number as a uint32_t array, unnecessary for now. */
/*
C uint32_t RFC_prime[] =
{
    0xFFFFFFFF, 0xFFFFFFFF, 0xC90FDAA2, 0x2168C234, 0xC4C6628B, 
    0x80DC1CD1, 0x29024E08, 0x8A67CC74, 0x020BBEA6, 0x3B139B22, 
    0x514A0879, 0x8E3404DD, 0xEF9519B3, 0xCD3A431B, 0x302B0A6D, 
    0xF25F1437, 0x4FE1356D, 0x6D51C245, 0xE485B576, 0x625E7EC6, 
    0xF44C42E9, 0xA637ED6B, 0x0BFF5CB6, 0xF406B7ED, 0xEE386BFB,
    0x5A899FA5, 0xAE9F2411, 0x7C4B1FE6, 0x49286651, 0xECE45B3D,
    0xC2007CB8, 0xA163BF05, 0x98DA4836, 0x1C55D39A, 0x69163FA8, 
    0xFD24CF5F, 0x83655D23, 0xDCA3AD96, 0x1C62F356, 0x208552BB,
    0x9ED52907, 0x7096966D, 0x670C354E, 0x4ABC9804, 0xF1746C08, 
    0xCA18217C, 0x32905E46, 0x2E36CE3B, 0xE39E772C, 0x180E8603, 
    0x9B2783A2, 0xEC07A28F, 0xB5C55DF0, 0x6F4C52C9, 0xDE2BCBF6,
    0x95581718, 0x3995497C, 0xEA956AE5, 0x15D22618, 0x98FA0510,
    0x15728E5A, 0x8AACAA68, 0xFFFFFFFF, 0xFFFFFFFF
};
*/

/* RFC 2048 bit prime number as a base62 string, for use with GMP */
C char RFC_prime_b62str[] = "qMvq04wETHykwmBW2FBQZolzOg0jEuUURFM0SIJHKIV1icTUizH1bu9Lm9I0O2q0tr4wEPdNXkBkdIJtgCjJbiAyG9xQEHtxAYd4hoKRPGMxcnM0cfCE1spSNc4RuOFkgUURKGw3bIPLnmdTLb3lAvg8sOdFoXhsk6wwyzcPhFGbm7VypgXXbFH8F7tELKXQv99iQQpVHvDotGCO2rNCBBJkyL7GbtKAWbWKoGeNQwyeOLN2LPEvpAUrJZrSoZEOuRffqcCbhV1UBM9JZbOTvvw2936n5RJY69rqOqcuQ3yXy4lmKGwD6E2aEQdpgNva2MqmrkxlLqS2b38LXyEcVrX5";

MPZ modulus;

/* Initiate Diffie-Hellman shit */
C void initDH()
{
    mpz_init_set_str(modulus.mpz_s, RFC_prime_b62str, 62);
}