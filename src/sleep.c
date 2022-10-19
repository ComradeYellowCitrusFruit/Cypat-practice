/*
*
*   src/sleep.c
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

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "include/kill.h"
#include "include/guidefile.h"
#include "include/crypt/SHA256.h"
#include "include/eventLoop.h"
#include "include/log.h"
#include "include/integrity.h"

/* Sleep, creates the sleep file then kills the image */
NORETURN void sleep()
{
    log("sleep()");
    /* Open the sleep file */
    FILE *fsleep = fopen(SLEEPFILENAME, "w");
    log("Sleep file opened.");

    /* Create a buffer for all data used in checksum */
    uint8_t *tmpbuf = malloc(sizeof(GF_Header_t) + (gf_state.header.varCount * sizeof(var_t)));

    /* Collect all data for checksum */
    memcpy(tmpbuf, &(gf_state.header), sizeof(GF_Header_t));
    memcpy(tmpbuf + sizeof(GF_Header_t), gf_state.vars, gf_state.header.varCount * sizeof(uint16_t));
    
    /* Calculate checksum */
    uint8_t checksum[32];
    SHA256_M(tmpbuf, sizeof(GF_Header_t) + (gf_state.header.varCount * sizeof(var_t)), checksum);
    log("Data hash calculated.");

    /* Write checksum + data to file */
    fwrite(tmpbuf, sizeof(GF_Header_t) + (gf_state.header.varCount * sizeof(uint16_t)), 1, fsleep);
    fwrite(checksum, sizeof(uint8_t), 32, fsleep);
    log("Data and checksum written to sleep file.");
    
    /* Write null hash then calculate the correct value */
    uint8_t hash[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    fwrite(hash, sizeof(uint8_t), 32, fsleep);
    SHA256_F(fsleep, hash);
    log("'Chaining hash' calculated.");

    /* Write the 'chaining hash' in place of the null hash */
    fseek(fsleep, -32, SEEK_END);
    fwrite(hash, sizeof(uint8_t), 32, fsleep);
    log("'Chaining hash' appended to the data.");

    /* Save score */
    fwrite(gf_state.score, sizeof(int32_t), 1, fscore);
    log("Score saved");

    /* Close a bunch of files */
    fclose(fsleep);
    fclose(fscore);
    fclose(scoreLog);
    log("Closed the sleep file, the score file, and the score log.");

    /* Create the hash record */
    createRecord();

    /* Kill logging */
    log("fcloseall() and "SHUTDOWNCMD" will be called soon, logging is about to be killed.");
    finiLog();

    /* Close all files */
    fcloseall();

    /* Kill the image */
    system(SHUTDOWNCMD);
}