/*
*
*   include/integrity.h   
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

#ifndef INTEGRITY_H
#define INTEGRITY_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    /* Null terminated C string with a max size of 255 characters. */
    char Filename[256];
    uint8_t hash[32];
} Cache_entry_t;

extern FILE *hashRecord;
extern Cache_entry_t *cache;

#ifdef __unix__
#define HASH_RECORD_NAME "/CYPAT/HASH_RECORD"
#elif defined(_WIN32)
#define HASH_RECORD_NAME "C:/CYPAT/HASH_RECORD"
#endif

/* Generate the cache. */
void genCache();
/* Create the hash record */
void createRecord();
/* Perform an integrity check. */
bool checkIntegrity();
/* Verify the hash record's integrity. */
bool verifyHashRecord();

#endif