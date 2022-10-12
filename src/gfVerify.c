/*
*
*   src/gfVerify.c  
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

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/eventLoop.h"
#include "include/guidefile.h"
#include "include/crypt/SHA256.h"
#include "include/log.h"
#include "include/errors.h"

bool gf_verify()
{
    log("gf_verify()");
    uint8_t *tmpBuf = malloc(gf_state.header.size);
    GF_Footer_t footer;
    uint8_t hash[32];
    /* Get the footer, for the footer hash */
    fseek(guideFile, gf_state.header.foffset, SEEK_SET);
    fread(&footer, 1, sizeof(footer), guideFile);
    rewind(guideFile);
    /* Copy guidefile into ram temporarily */
    fread(tmpBuf, 1, gf_state.header.size, guideFile);
    /* Null out the hashes, so we can get a correct hash */
    memset(&((*(GF_Header_t*)tmpBuf).hash), 0, sizeof(uint8_t) * 32);
    memset(tmpBuf + gf_state.header.foffset, 0, sizeof(uint8_t) * 32);
    SHA256_M(tmpBuf, gf_state.header.size, hash);
    if(memcmp(hash, gf_state.header.hash, sizeof(uint8_t) * 32) == 0 && memcmp(hash, footer.hash, sizeof(uint8_t) * 32) == 0)
    {
        log("Guidefile is valid, returning");
        return true;
    }
    else
    {
        errLog("Invalid guidefile detected, returning.", GUIDEFILE_INVALID);
        return false;
    }
}