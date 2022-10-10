/*
*
*   src/crypt/rand.c  
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

/* Windows is a bitch */
#ifdef __unix___
#include <stdio.h>
#elif defined(_WIN32)
#include <Windows.h>
#endif
#include <stdint.h>
#include "include/crypt/rand.h"

/* Get a cryptographically secure random byte */
uint8_t getRandByte();
{
    #ifdef __unix__
    FILE *urand = fopen("/dev/urandom", "r");
    uint8_t ret = (uint8_t)fgetc(urand);
    fclose(urand);
    return ret;
    #elif defined(_WIN32)
    HCRYPTPROV p;
    ULONG i;
    uint8_t ret;
    CryptAcquireContext(&p, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
    CryptGenRandom(p, 1, (BYTE*)&ret);
    CryptReleaseContext(p, 0);
    return ret;
    #endif
}
/* Get count number of cryptographically secure random bytes and place them at dest */
void getRandBytes(void *dest, size_t count)
{
    #ifdef __unix__
    FILE *urand = fopen("/dev/urandom", "r");
    fread(dest, sizeof(uint8_t), count, urand);
    fclose(urand);
    return;
    #elif defined(_WIN32)
    HCRYPTPROV p;
    ULONG i;
    uint8_t ret;
    CryptAcquireContext(&p, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);
    CryptGenRandom(p, sizeof(BYTE) * count, (BYTE*)dest);
    CryptReleaseContext(p, 0);
    return;
    #endif
}