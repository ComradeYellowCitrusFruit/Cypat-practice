/*
*
*   src/integrity.c
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

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "include/crypt/SHA256.h"
#include "include/guidefile.h"
#include "include/integrity.h"

/* The hash record*/
FILE *hashRecord;
/* Pointer to the cache */
Cache_entry_t *cache;
/* Size of the cache in bytes */
size_t cacheSize;

bool checkIntegrity()
{
    if(!gf_verify())
        return false;
    else if(!verifyHashRecord())
        return false;
    else
    {
        for(size_t i = 0; i < cacheSize/sizeof(Cache_entry_t); i++)
        {
            uint8_t hash[32];
            FILE *tmp = fopen(cache[i].Filename, "r");
            SHA256_F(tmp, hash);
            if(memcpy(hash, cache[i].hash, 32 * sizeof(uint8_t)) != 0)
                return false;
        }
    }
}

bool verifyHashRecord();