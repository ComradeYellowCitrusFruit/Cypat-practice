/*
*
*   include/errors.h
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

#ifndef ERROR_CODES_H
#define ERROR_CODES_H

#define INCOMPATIBLE_MAJOR_VER 1
#define INCOMPATIBLE_MINOR_VER 2

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
#define ALLOCA_UNAVALIBLE 0xCAAAAAAA

#define FILESYSTEM_INVALID_GUIDEFILE 0xE0000000
#define FILESYSTEM_FOPEN_ERROR 0xE0000001
#define FILESYSTEM_FINPUT_ERROR 0xE0000002
#define FILESYSTEM_FOUTPUT_ERROR 0xE0000002
#define FILESYSTEM_FCLOSE_ERROR 0xE0000003
#define FILESYSTEM_CRITICAL_TAMPERING 0xEFFFFFFF

#endif