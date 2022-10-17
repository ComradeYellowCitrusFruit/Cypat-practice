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
#include <stdlib.h>
#include "include/crypt/SHA256.h"
#include "include/log.h"
#include "include/guidefile.h"
#include "include/integrity.h"

#ifdef _WIN32

#include <io.h>

#define F_OK 0
#define access _access

#elif defined(__unix__)

#include <unistd.h>

#endif

/* The hash record*/
FILE *hashRecord;
/* Pointer to the cache */
Cache_entry_t *cache;
/* Size of the cache in bytes */
size_t cacheSize;

/* Since being cross platform is a pain in the ass let's save this for later. */
static inline bool fileExists(char *fname)
{
    /* For once being cross platform isn't that much of a pain in the ass*/
    if (access(fname, F_OK) == 0)
        return true;
    return false;
}

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
            if(memcmp(hash, cache[i].hash, 32 * sizeof(uint8_t)) != 0)
                return false;
        }
        
        if(fileExists(LOGPATH"/CYPAT.log") == false || fileExists(LOGPATH"/CYPAT.err.log") == false)
            return false;
    }
}

bool verifyHashRecord()
{
    fseek(hashRecord, -32 * sizeof(uint8_t), SEEK_END);
    size_t recordSize = ftell(hashRecord);
    void *buf = calloc(recordSize + (32 * sizeof(uint8_t)), sizeof(uint8_t));
    rewind(hashRecord);
    fread(buf, sizeof(uint8_t), recordSize, hashRecord);
    uint8_t hash[32];
    SHA256_M(buf, recordSize + (32 * sizeof(uint8_t)), hash);

    uint8_t recordedHash[32];
    fseek(hashRecord, -32 * sizeof(uint8_t), SEEK_END);
    fread(recordedHash, sizeof(uint8_t), 32, hashRecord);
    rewind(hashRecord);

    free(buf);

    if(memcmp(hash, recordedHash, 32 * sizeof(uint8_t)) == 0)
        return true;
    else
        return false;
}