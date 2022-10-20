/*
*
*   include/log.h   
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

#ifndef LOG_H
#define LOG_H

#include <stdint.h>

#ifdef __unix__
#define LOGPATH "/var/log"
#elif defined(_WIN32)
#define LOGPATH "C:/CYPAT_logs" 
#endif

#define GENERAL 0
#define ERROR 1
#define NETWORK 2
#define DEBUG 3

#define INFORMATIONAL 3
#define WARNING 2
#define ERROR 1
#define LIVE_OR_DIE 0
#define CRITICAL LIVE_OR_DIE
#define FATAL -1

void initLog();

/* Log a message, works just like printf. */
void log(char *msg, ...);
/* Log an error, logs to a specific file as well as the general log file, it logs errno, the errCode, and the errMsg, which is a string formated just like printf. */
void errLog(char *errMsg, int urgency, uint32_t errCode, ...);

#ifdef NETWORK_GENERAL_DEFINES_H
/* Log a network log message, logs to a specific file as well as the general log file, it logs packetDesig and msg, acts just like printf for the string formating */
void netLog(char *msg, Packet_Desig_t packetDesig, ...);
/* Log a network error message, follows the same rules as netLog(), and logs to the error log file. */
void netErrLog(char *errMsg, int urgency, Packet_Desig_t packetDesig, ...);
#endif

/* Log a message if debug is true, functions like log() otherwise */
void debugLog(char *msg, ...);

/* Kill logging system, close the files */
void finiLog();

#endif