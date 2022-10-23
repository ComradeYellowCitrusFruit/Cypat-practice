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

#define GENERAL_INCOMPATIBLE_MAJOR_VER 0x00FFFF01
#define GENERAL_INCOMPATIBLE_MINOR_VER 0x00FFFF02

#define NETWORK_SOCKET_OPEN_ERR 0x80534F45
#define NETWORK_SOCKET_CLOSE_ERR 0x80534345
#define NETWORK_PACKET_SEND_ERR 0x80505345
#define NETWORK_PACKET_RECIEVE_ERR 0x80505245
#define NETWORK_DIFFIE_HELLMAN_INIT_FAILURE 0x80444849
#define NETWORK_DIFFIE_HELLMAN_INVALID_EXCHANGE 0x80494448
#define NETWORK_UNIQUE_ID_INVALID 0x80554949

#define MALLOC_NOMEM 0xC0FFFF3B
#define CALLOC_NOMEM MALLOC_NOMEM
#define MALLOC_ALLOCATION_FAILURE 0xC0000001
#define CALLOC_ALLOCATION_FAILURE 0xC0000002
#define ALLOCA_ALLOCATION_FAILURE 0xC0000003
#define ALLOCA_UNAVALIBLE 0xC0262F3D

#define FILESYSTEM_FOPEN_ERROR 0xE0466F45
#define FILESYSTEM_FINPUT_ERROR 0xE0464945
#define FILESYSTEM_FOUTPUT_ERROR 0xE0464F45
#define FILESYSTEM_FCLOSE_ERROR 0xE0464345
#define FILESYSTEM_INVALID_HASH_RECORD 0xE0FFFFFF
#define FILESYSTEM_CRITICAL_TAMPERING 0xE0FFFFFF

#define GUIDEFILE_INVALID 0xF0FFFF5E
#define GUIDEFILE_INVALID_CONDITION 0xF0FFFFA1

#define CPU_32BITS 0xF8AAAAAA
#define CPU_16BITS 0xF8FFFF16
#define CPU_NOT_X86 0xF8783836
#define CPU_AES_EXTENSIONS_UNAVALIBLE 0xF8414553

/* Not sure where else to classify this */
#define CPU_IMPOSSIBLE_EVENT_OCCURED 0xF8FFFFE7
#define CPU_ILLEGAL_INSTRUCTION 0xF8FFFF31
#define CPU_RECIEVED_SIGILL CPU_ILLEGAL_INSTRUCTION

#endif