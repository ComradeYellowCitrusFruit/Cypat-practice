/*
*
*   src/initconds.c
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

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "include/guidefile.h"
#include "include/conditions.h"
#include "include/eventLoop.h"
#include "include/log.h"

void runInitConds()
{
    log("Starting to execute initconditions.");
    fseek(guideFile, gf_state.header.offset, SEEK_SET);
    for(size_t i = 0; i < gf_state.header.conditionCount; i++)
    {
        COND_Header_t header;
        fread(&header, sizeof(COND_Header_t), 1, guideFile);
        if(header.typeCode == 0xFE)
        {
            COND_Initcond_t cond;
            fread(&cond, sizeof(COND_Initcond_t), 1, guideFile);
            COND_var_t *vars = malloc(sizeof(COND_var_t) * cond.varCount);
            fread(vars, sizeof(COND_var_t), cond.varCount, guideFile);
            for(uint16_t j = 0; j < cond.varCount; i++)
            {
                gf_state.vars[vars[j].varCode] = vars[j].val;
                log("Var %"PRIu16" has been initalized to %"PRId32, vars[j].varCode, vars[j].val);
            }
        }
        fseek(guideFile, header.nextOffset, SEEK_SET);
    }
    rewind(guideFile);
    log("Finished executing initconditions.");
    return;
}