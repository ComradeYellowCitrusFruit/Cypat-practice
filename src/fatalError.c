/*
*
*   src/fatalError.c  
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

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "include/log.h"
#include "include/kill.h"

/* Fatal error */
NORETURN void fatalError(bool perm)
{
    /* For our purposes here, we can't assume anything other than initLog() having been called, so we won't save the score or anything. */
    log("fatalError()");

    if(perm)
    {
        FILE *NOBOOT = fopen(NOBOOTFILENAME, "w");
        fprintf(NOBOOT, NOBOOTSTR);
        log("NOBOOT file created.");
    }
    
    /* Kill logging */
    finiLog();

    /* Close all files */
    fcloseall();

    /* Kill the image */
    system(SHUTDOWNCMD);
}