/*
*
*   include/errors.h
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

#ifndef ERROR_CODES_H
#define ERROR_CODES_H

/*  Error code definitions 
*   The most significant byte of each error code is significant, determining what the error code is for
*       0x00 - General, no specific module or functional category
*       0x80 - Networking module and functions, also includes Diffie-Hellman
*       0xC0 - Memory allocation and management
*       0xE0 - Filesystem, not including guidefiles
*       0xF0 - Guidefiles and conditions
*       0xF8 - Cpu and hardware info
*   The middle 2 bytes of each error code tell if it's fatal, or not
*       0xFFFF - Fatal
*       0xAAAA - Not fatal, though significant
*       Anything else - Not fatal
*   The least significant byte of each error code is insignificant, they hold no value
*/

#define FATAL_BYTES 0x00FFFF00
#define NONFATAL_SIG_BYTES 0x00AAAA00

#define NETWORK 0x80000000
#define MEM 0xC0000000
#define FILESYSTEM 0xE0000000
#define GUIDEFILE 0xF0000000
#define CPU 0xF8000000

#define INCOMPATIBLE_MAJOR_VER 0x00FFFF01
#define INCOMPATIBLE_MINOR_VER 0x00FFFF02

#define NETWORK_SOCKET_OPEN_ERR 0x80000000
#define NETWORK_SOCKET_CLOSE_ERR 0x80000001
#define NETWORK_PACKET_SEND_ERR 0x80000002
#define NETWORK_PACKET_RECIEVE_ERR 0x80000003
#define NETWORK_UNIQUE_ID_INVALID 0x80000004

#define MALLOC_NOMEM 0xC0000000
#define CALLOC_NOMEM MALLOC_NOMEM
#define ALLOCA_NOMEM CALLOC_NOMEM
#define MALLOC_ALLOCATION_FAILURE 0xC0000001
#define CALLOC_ALLOCATION_FAILURE 0xC0000002
#define ALLOCA_ALLOCATION_FAILURE 0xC0000003
#define ALLOCA_UNAVALIBLE 0xC0AAAAAA

#define FILESYSTEM_FOPEN_ERROR 0xE0000001
#define FILESYSTEM_FINPUT_ERROR 0xE0000002
#define FILESYSTEM_FOUTPUT_ERROR 0xE0000002
#define FILESYSTEM_FCLOSE_ERROR 0xE0000003
#define FILESYSTEM_CRITICAL_TAMPERING 0xE0FFFFFF

#define GUIDEFILE_INVALID 0xF0FFFF00
#define GUIDEFILE_INVALID_CONDITION 0xF0FFFF01

#define CPU_32BITS 0xF8AAAAAA
#define CPU_16BITS 0xF8FFFFFF
#define CPU_NOT_X86 0xF8783836
#define CPU_AES_EXTENSIONS_UNAVALIBLE 0xF8414553

#endif