/*
*
*   src/guidefile.c  
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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "include/eventLoop.h"
#include "include/guidefile.h"
#include "include/log.h"

GF_STATE_t gf_state;

void initState()
{
    fread(&(gf_state.header), sizeof(GF_Header_t), 1, guideFile);
    rewind(guideFile);
    log("Guidefile header read and initialized in gf_state at address %p.", (void*)&(gf_state.header));
    gf_state.score = &score;
    log("gf_state.score, located at address %p, initialized to address %p.", (void*)&(gf_state.score), (void*)&score);
    gf_state.vars = calloc(gf_state.header.varCount, sizeof(variable_t));
    log("%zu bytes allocate for "PRIu16" variables allocated at address %p.", gf_state.header.varCount * sizeof(int32_t), gf_state.header.varCount, (void*)(gf_state.vars));
    log("gf_state fully initalized.");
    return;
}