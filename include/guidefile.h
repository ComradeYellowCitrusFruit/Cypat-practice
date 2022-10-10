/*
*
*   include/guidefile.h   
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

#ifndef GUIDEFILES_H
#define GUIDEFILES_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    /* Condition start offset */
    uint32_t offset;
    /* Footer offset */
    uint32_t foffset;
    /* File size */
    uint32_t size;
    /* Major version number */
    uint16_t majorVer;
    /* Minor version number */
    uint16_t minorVer;
    /* Patch number*/
    uint16_t patch;
    /*  Code for alpha, beta, or release version
    *   0xA for Alpha
    *   0xB for Beta
    *   0xF for Release
    */
    uint8_t alphaCode;
    /*  Code for the operating system for the file.
    *   0x01 for Windows
    *   0x10 for Windows Server
    *   0x02 for Ubuntu
    *   0x20 for Ubuntu Server
    *   0x03 for Debian
    *   0x04 for Kali Linux
    *   0x05 for another Linux distribution
    *   0xB1 for OpenBSD
    *   0xB2 for FreeBSD
    */
    char OSCODE;
    /* Operating system version numbers, minimums, anyway. */
    uint16_t OS_majorVer;
    uint16_t OS_minorVer;
    uint16_t os_patch;
    /* Number of conditions */
    uint16_t conditionCount;
    /* Time for timer in minutes, 0 or -1 will yield no timer. */
    uint32_t time;
    /* IPv4 or IPv6 */
    bool IPv4;
    /* IP of server to connect to, IP should be in utf-8 or ascii, null terminating, port is 44252. */
    char serverIP[255];
    /* Number of variables, primarily for metaconditions */
    uint16_t varCount;
    /* Guidefile hash, to confirm validity. */
    uint8_t hash[32];
} GF_Header_t;

typedef struct
{
    /* Condition start offset */
    uint32_t offset;
    /* Header offset */
    uint32_t hoffset;
    /* File size */
    uint32_t size;
    /* Guidefile hash, to confirm validity. */
    uint8_t hash[32];
} GF_Footer_t;

typedef int32_t variable_t, var_t;

typedef struct
{
    GF_Header_t header;
    variable_t *vars;
    int32_t *score;
} GF_STATE_t;

extern GF_STATE_t gf_state;

/* Initializes the guidefile state. */
void initState();

#endif