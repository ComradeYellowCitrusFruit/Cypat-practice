/*
*
*   include/state.h   
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
#ifndef PROGRAM_STATE_H
#define PROGRAM_STATE_H

#include <stdint.h>
#include <stdbool.h>

/* A structure containing arguments to use */
typedef struct
{
    uint8_t verbose : 1;
    uint8_t notifications : 1;
    uint8_t debug : 1;
    uint8_t anon : 1;
    uint8_t pause : 1;
    uint8_t allocaEnabled : 1;
    uint16_t pauseTime;
} Args_t;

typedef struct
{
    /* Our arguments */
    Args_t args;
    /* Any of our errors, except CPU errors */
    uint32_t internalErrno;
    /* Our AES key, if we are using it right now */
    uint8_t key[32];
    /* Did we wake from a sleep state */
    bool slept;
    #ifdef __linux__
        /*  Linux distro currently running, important for a number of reasons
        *   Ubuntu - 0x00
        *   Debian - 0x10
        *   Arch - 0x20
        *   Fedora - 0x30
        */
        uint8_t distro;
    #elif defined(_WIN32)
        /*  Version of Windows running,
        *   Windows 10 - 0x10
        *   Windows Server 2016 - 0x16
        *   Windows 11 - 0x11
        *   Windows Server 2022 - 0x22
        */
        uint8_t winVer;
    #endif
} PROGRAM_state_t;

extern PROGRAM_state_t state;

/* Initialize the program state */
void initPState();

#endif