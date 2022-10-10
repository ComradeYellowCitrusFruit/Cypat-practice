/*
*
*   src/fstateconds.c   
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

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "include/crypt/SHA256.h"
#include "include/log.h"
#include "include/errors.h"
#include "include/conditions.h"
#include "include/eventLoop.h"

#ifdef _WIN32

#include <io.h>
#define F_OK 0
#define access _access

#define COMMAND_APPEND " > C:/tmp/CYPAT_COND"
#define OSVER_COMMAND "systeminfo > C:/tmp/CYPAT_OSVER; grep \"OS Version:\" C:/tmp/CYPAT_OSVER > C:/tmp/CYPAT_COND "
#define COND_TEMP_FILE_NAME "C:/tmp/CYPAT_COND"
#elif defined(__unix__)

#include <unistd.h>

#define COMMAND_APPEND " > /tmp/CYPAT_COND"
#define OSVER_COMMAND "uname -srm > /tmp/CYPAT_COND"
#define COND_TEMP_FILE_NAME "/tmp/CYPAT_COND"
#endif

#define CALCPTR(PTR, ADD) (void*)((uintptr_t)PTR + ADD)

/* Since being cross platform is a pain in the ass let's save this for later. */
static inline bool fileExists(char *fname)
{
    /* For once being cross platform isn't that much of a pain in the ass*/
    if (access(fname, F_OK) == 0)
        return true;
    return false;
}

void runFstate(COND_fstate_t *cond)
{
    char *fname = CALCPTR(cond, cond->nameOffset);
    if(cond->existsOrState)
    {
        uint8_t fstate[32];
        FILE *file = fopen(fname, "r");
        SHA256_F(file, fstate);
        if(memcmp(fstate, cond->hash, sizeof(uint8_t) * 32) == 0)
            runEffect(cond->effect);
        fclose(file);
    }
    else
    {
        if(cond->existsOrNot == fileExists(fname))
            runEffect(cond->effect);
    }
    return;
}

void runCresult(COND_cresult_t *cond)
{
    char *cmd = malloc(strlen(CALCPTR(cond, cond->commandOffset)) + sizeof(COMMAND_APPEND));
    strcpy(cmd, CALCPTR(cond, cond->commandOffset));
    strcat(cmd, COMMAND_APPEND);
    log("Running command \"%s\"", cmd);
    system(cmd);
    FILE *res = fopen(COND_TEMP_FILE_NAME, "r");
    uint8_t cres[32];
    SHA256_F(res, cres);
    if(memcmp(cres, cond->hash, sizeof(uint8_t) * 32) != false)
        runEffect(cond->effect);
    fclose(res);
    return;
}

void runOSVER(COND_OSVER_t *cond)
{
    FILE *file = fopen(COND_TEMP_FILE_NAME, "r");
    log("Checking OS version with command \"%s\"", OSVER_COMMAND);
    system(OSVER_COMMAND);
    uint8_t hash[32];
    SHA256_F(file, hash);
    if(memcmp(hash, cond->hash, sizeof(uint8_t) * 32) != false)
        runEffect(cond->effect);
    fclose(file);
    return;
}