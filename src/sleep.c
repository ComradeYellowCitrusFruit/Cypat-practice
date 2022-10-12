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

#ifdef __unix__
#define SLEEPFILENAME "/CYPAT/SLEEP"
#define SHUTDOWNCMD "shutdown -h now"
#elif defined(_WIN32)
#define SLEEPFILENAME "C:/CYPAT/SLEEP"
#define SHUTDOWNCMD "shutdown -s -f -t 0"
#endif

/* Sleep, creates the sleep file then kills the image */
NORETURN void sleep()
{
    log("sleep()");
    /* Open the sleep file */
    FILE *fsleep = fopen(SLEEPFILENAME, "w");
    log("Sleep file opened.");

    /* Create a buffer for all data used in checksum */
    uint8_t *tmpbuf = malloc(sizeof(GF_Header_t) + (gf_state.header.varCount * sizeof(uint16_t)) + sizeof(time_t));

    /* Collect all data for checksum */
    memcpy(tmpbuf, &(gf_state.header), sizeof(GF_Header_t));
    memcpy(tmpbuf + sizeof(GF_Header_t), gf_state.vars, gf_state.header.varCount * sizeof(uint16_t));
    time_t tmptime;
    time(&tmptime);
    memcpy(tmpbuf + gf_state.header.varCount * sizeof(uint16_t) + sizeof(GF_Header_t), &tmptime, sizeof(time_t));

    /* Calculate checksum */
    uint8_t checksum[32];
    SHA256_M(tmpbuf, sizeof(GF_Header_t) + (gf_state.header.varCount * sizeof(uint16_t)) + sizeof(time_t), checksum);
    log("Checksum calculated.");

    /* Write checksum + data to file */
    fwrite(tmpbuf, 1, sizeof(GF_Header_t) + (gf_state.header.varCount * sizeof(uint16_t)) + sizeof(time_t), fsleep);
    fwrite(checksum, sizeof(uint8_t), 32, fsleep);
    log("Data and checksum written to sleep file.");
    fclose(fsleep);
    log("Sleep file closed.");
    free(tmpbuf);

    /* Save score */
    fwrite(gf_state.score, sizeof(int32_t), 1, fscore);
    log("Score saved");

    /* Close all files */
    fclose(fscore);
    fclose(scoreLog);
    log("Score file and score log closed.");

    /* Kill logging */
    log("fcloseall() and "SHUTDOWNCMD" will be called soon, logging is about to be killed.");
    finiLog();

    /* Close all files */
    fcloseall();

    /* Kill the image */
    system(SHUTDOWNCMD);
}