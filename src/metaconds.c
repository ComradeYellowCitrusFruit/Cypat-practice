/*
*
*   src/metaconds.c
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

void runMetacond(COND_Metacond_t *cond)
{
    COND_effect_t *effect = (COND_effect_t*)((uintptr_t)cond +  sizeof(uint16_t));
    for(int i = 0; i < cond->varCount; i++, effect++)
        runEffect(*effect);
}