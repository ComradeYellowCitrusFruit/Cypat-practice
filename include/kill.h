/*
*
*   include/kill.h   
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

#ifndef PROGRAM_EXIT_H
#define PROGRAM_EXIT_H

#ifdef _GNUC_
#define NORETURN __attribute__((noreturn))
#endif

/* Disgraceful fatal error */
NORETURN void disgracefulFatalErr();

/* Graceful fatal error */
NORETURN void gracefulFatalErr();

/* Disgraceful exit, in case of foul play */
NORETURN void disgracefulExit();

/* Graceful exit, for final scoring */
NORETURN void gracefulExit();

/* Sleep, creates the sleep file then kills the image */
NORETURN void sleep();

#endif