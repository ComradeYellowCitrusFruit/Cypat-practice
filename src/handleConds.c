/*
*
*   src/handleConds.c
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
#include <stdlib.h>
#include "include/eventLoop.h"
#include "include/conditions.h"
#include "include/guidefile.h"
#include "include/log.h"
#include "include/errors.h"

#define CALCPTR(PTR, ADD) (void*)((uintptr_t)PTR + ADD)

/* Handle conditions */
void runConds()
{
    log("runConds()");
    COND_Header_t condH;
    uint32_t offset = gf_state.header.offset;
    while(true)
    {
        fseek(guideFile, offset, SEEK_SET);
        fread(&condH, 1, sizeof(COND_Header_t), guideFile);
        fseek(guideFile, offset, SEEK_SET);
        uint8_t *condBuf = malloc(condH.condSize);
        fread(condBuf, sizeof(uint8_t), condH.condSize, guideFile);
        switch(condH.typeCode)
        {
            case 0x00:
                runFstate(CALCPTR(condBuf, sizeof(COND_Header_t)));
                break;
            case 0x01:
                runDirExists(CALCPTR(condBuf, sizeof(COND_Header_t)));
                break;
            case 0x02:
                runFstate(CALCPTR(condBuf, sizeof(COND_Header_t)));
                break;
            case 0x03:
                runAppInstall(CALCPTR(condBuf, sizeof(COND_Header_t)));
                break;
            case 0x04:
                runCresult(CALCPTR(condBuf, sizeof(COND_Header_t)));
                break;
            case 0x05:
                runOSVER(CALCPTR(condBuf, sizeof(COND_Header_t)));
                break;
            case 0xFF:
                runMetacond(CALCPTR(condBuf, sizeof(COND_Header_t)));
                break;
            default:
                errLog("Invalid condition detected.", FATAL, GUIDEFILE_INVALID_CONDITION);
        }
        offset = condH.nextOffset;
        free(condBuf);
    }
    rewind(guideFile);
    log("All conditions handled successfully, returning");
    return;
}