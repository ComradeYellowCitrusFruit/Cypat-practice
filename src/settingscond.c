/*
*
*   src/settingscond.c   
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

#define CALCPTR(PTR, ADD) (void*)((uintptr_t)PTR + ADD)

/* A lot of this code could be reused for a "find in file" function */
void runSetting(COND_SETTING_t *cond)
{
    FILE *file = fopen(CALCPTR(cond, cond->fnameOffset), "r");
    uint8_t *setbuf = malloc(cond->settingSize);
    memcpy(setbuf, CALCPTR(cond, cond->settingOffset), cond->settingSize);
    fseek(file, 0, SEEK_END);
    size_t fsize = ftell(file);
    rewind(file);
    uint8_t *tmpbuf = malloc(cond->settingSize);
    for(size_t i = 0; i + cond->settingSize < fsize; i++)
    {
        fseek(file, i, SEEK_SET);
        fread(tmpbuf, sizeof(uint8_t), cond->settingSize, file);
        if(memcmp(tmpbuf, setbuf, cond->settingSize) == 0)
        {
            runEffect(cond->effect);
            fclose(file);
            free(setbuf);
            free(tmpbuf);
            return;
        }
        rewind(file);
    }
    return;
}