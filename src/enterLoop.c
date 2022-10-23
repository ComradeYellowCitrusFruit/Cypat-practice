/*
*
*   src/enterLoop.c  
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

#ifdef __unix__
#include <unistd.h>
#elif defined(_WIN32)
#endif
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "include/eventLoop.h"
#include "include/log.h"
#include "include/guidefile.h"
#include "include/errors.h"
#include "include/kill.h"
#include "include/integrity.h"
#include "include/state.h"

extern uint8_t majorVer;
extern uint8_t minorVer;
extern uint8_t patch;

/* Enter the main event loop. Not that complex. */
NORETURN void enterLoop()
{
    log("enterLoop()");
    fscore = fopen(scoreFilePath, "r+");
    log("Score file opened");
    scoreLog = fopen(scoreLogPath, "a+");
    log("Score log opened");
    guideFile = fopen(guideFilePath, "r");
    log("Guidefile oppened");
    initState(guideFile);

    genCache();
    if(state.internalErrno == FILESYSTEM_INVALID_HASH_RECORD)
        fatalError(true);

    if(!gf_verify())
        fatalError(true);

    if(gf_state.header.majorVer != majorVer)
    {
        errLog("gf_state.header.majorVer == %"PRIu8", not %"PRIu8, FATAL, GENERAL_INCOMPATIBLE_MAJOR_VER, gf_state.header.majorVer, majorVer);
    }
    if(gf_state.header.minorVer != minorVer)
    {
        errLog("gf_state.header.minorVer == %"PRIu8", not %"PRIu8, FATAL, GENERAL_INCOMPATIBLE_MINOR_VER, gf_state.header.minorVer, minorVer);
    }

    if(gf_state.header.majorVer != majorVer || gf_state.header.minorVer != minorVer)
        fatalError(true);

    /* Oh boy an infinite loop*/
    log("The environment necessary for mainLoop() has been set up.");
    while(1)
        mainLoop();
}