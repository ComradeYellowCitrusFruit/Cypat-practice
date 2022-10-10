/*
*
*   src/eventLoop_vars.c  
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
#include "include/eventLoop.h"

/* Score file. */
FILE *fscore;
/* Score log. */
FILE *scoreLog;
/* Score. */
int32_t score;

/* The file that governs over the scoring for the image. */
FILE *guideFile;

#ifdef __unix__
char scoreFilePath[] = "/CYPAT/SCORE";
char scoreLogPath[] = "/CYPAT/SCORE_LOG";
char guideFilePath[] = "/CYPAT/GUIDEFILE";
#elif defined(_WIN32)
char scoreFilePath[] = "C:/CYPAT/SCORE";
char scoreLogPath[] = "C:/CYPAT/SCORE_LOG";
char guideFilePath[] = "C:/CYPAT/GUIDEFILE";
#endif