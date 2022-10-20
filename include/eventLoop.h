/*
*
*   include/eventLoop.h
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

#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <stdio.h>
#include <stdint.h>
#include "conditions.h"

#define NORETURN __attribute__((noreturn))

/* Score file. */
extern FILE *fscore;
/* Score log. */
extern FILE *scoreLog;
/* Score. */
extern int32_t score;

/* The file that governs over the scoring for the image. */
extern FILE *guideFile;

#ifdef __unix__
extern char scoreFilePath[];
extern char scoreLogPath[];
extern char guideFilePath[];
#elif defined(_WIN32)
extern char scoreFilePath[];
extern char scoreLogPath[];
extern char guideFilePath[];
#endif

/* Enter the main event loop. Not that complex. */
NORETURN void enterLoop();
/* Self explanitory */
int mainLoop();

/* Handle conditions */
void runConds();
/* Execute an effect */
void runEffect(COND_effect_t effect);

#endif