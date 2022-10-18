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
#include "include/errors.h"
#include "include/log.h"
#include "include/guidefile.h"
#include "include/integrity.h"

#ifdef _WIN32

#include <Windows.h>
#include <io.h>

#define F_OK 0
#define access _access

#elif defined(__unix__)

#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>

#endif

/* The hash record*/
FILE *hashRecord;
/* Pointer to the cache */
Cache_entry_t *cache;
/* Size of the cache in bytes */
size_t cacheSize;
/* Cache entry count */
size_t entryCount = 0;

/* Since being cross platform is a pain in the ass let's save this for later. */
static inline bool fileExists(char *fname)
{
    /* For once being cross platform isn't that much of a pain in the ass*/
    if (access(fname, F_OK) == 0)
        return true;
    return false;
}

void genCache()
{
    cache = malloc(sizeof(Cache_entry_t));
    log("genCache()");

    #ifdef __unix__
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    dp = opendir("/CYPAT");
    chdir("/CYPAT");
    /* Continue for each entry in /CYPAT */
    while((entry = readdir(dp)) != NULL)
    {
        stat(entry->d_name,&statbuf);
        /* entry is a file */
        if(S_ISREG(statbuf.st_mode))
        {
            if(strcmp(entry->d_name, "/CYPAT/GUIDEFILE") == 0)
                log("Guidefile encountered in genCache(), skipping. ");
            else
            {
                log("Generating cache entry for %s", entry->d_name);
                /* Open the proper file */
                FILE *file = fopen(entry->d_name, "r");
                uint8_t hash[32];

                /* Set the cache variables to the proper values */
                entryCount++;
                cacheSize = sizeof(Cache_entry_t) * entryCount;

                /* Reallocate the cache */
                cache = realloc(cache, cacheSize);

                /* Hash the file */
                SHA256_F(file, hash);

                /* Set the cache entry up */
                memcpy(&cache[entryCount-1].hash, hash, 32 * sizeof(uint8_t));
                strncpy(&cache[entryCount-1].Filename, entry->d_name, 255);

                /* Close the file */
                fclose(file);
            }
        }
    }
    #elif defined(_WIN32)
    /* We'll need this for FindFirstFileA() and FindNextFileA() */
    WIN32_FIND_DATAA fData;
    HANDLE h;
    h = FindFirstFileA("C:/CYPAT/*.*", &fData);

    while(h != INVALID_HANDLE_VALUE)
    {
        if(strcmp(fData.cFileName, "C:/CYPAT/GUIDEFILE") == 0)
            log("Guidefile encountered in genCache(), skipping. ");
        else
        {
            log("Generating cache entry for %s", fData.cFileName);
            FILE *file = fopen(fData.cFileName, "r");
            uint8_t hash[32];

            /* Set the cache variables to the proper values */
            entryCount++;
            cacheSize = sizeof(Cache_entry_t) * entryCount;

            /* Reallocate the cache */
            cache = realloc(cache, cacheSize);

            /* Hash the file */
            SHA256_F(file, hash);

            /* Set the cache entry up */
            memcpy(&cache[entryCount-1].hash, hash, 32 * sizeof(uint8_t));
            strncpy(&cache[entryCount-1].Filename, fData.cFileName, 255);

            /* Close the file */
            fclose(file);
        }

        FindNextFileA(h, &fData);
    }
    #endif

    log("genCache() has finished, cache size is %zu, number of entries is %zu, returning.", cacheSize, entryCount);

    return;
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