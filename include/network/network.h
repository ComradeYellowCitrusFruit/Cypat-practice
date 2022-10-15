/*
*
*   include/network/network.h
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
#ifndef NETWORK_GENERAL_DEFINES_H
#define NETWORK_GENERAL_DEFINES_H

#include <stdint.h>

/* This is a header for general network shit, primarily packet designations */

/*  Packet designation codes
*   Similarly to error codes, these are standardized, and have meaning, however, they are only 24 bits
*
*   The most significant byte has significance indicating what the packet is for
*       0x80 - Diffie-Hellman handshake
*       0xC0 - Unique ID handshake
*       0xD0 - Login handshake
*       0xF0 - Log transfer
*       0xFF - Foul play detected
*
*   The rest of the code is insignifcant, only needs to be unique, nothing more
*/

#define DIFFIE_HELLMAN 0x80
#define UID 0xC0
#define LOGIN 0xD0
#define LOG_TRANSFER 0xF0
#define FOUL_PLAY 0xFF

#define CALCCODE(sig, val) (sig << 16 | val)

#define DIFFIE_HELLMAN_INIT CALCCODE(DIFFIE_HELLMAN, 0)
#define DIFFIE_HELLMAN_CME_EXCHANGE CALCCODE(DIFFIE_HELLMAN, 1)
#define DIFFIE_HELLMAN_FINI CALCCODE(DIFFIE_HELLMAN, 0xFFFF)

#define UID_REQUEST CALCCODE(UID, 0xAAAA)
#define UID_SEND CALCCODE(UID, 0x5555)

#define LOGIN_INIT CALCCODE(LOGIN, 0)
#define LOGIN_IDCODE_SEND CALCCODE(LOGIN, 0xFF00)
#define LOGIN_PASSWD_SEND CALCCODE(LOGIN, 0xFF)
#define LOGIN_FINI CALCCODE(LOGIN, 0xFFFF)

#define LOG_TRANSFER_INIT CALCCODE(LOG_TRANSFER, 0)
#define LOG_TRANSFER_SCORE CALCCODE(LOG_TRANSFER, 0xF000)
#define LOG_TRANSFER_SCORE_LOG CALCCODE(LOG_TRANSFER, 0xF00)
#define LOG_TRANSFER_LOG CALCCODE(LOG_TRANSFER, 0xF0)
#define LOG_TRANSFER_ERRLOG CALCCODE(LOG_TRANSFER, 0xF)

#define FOUL_PLAY_SEND CALCCODE(FOUL_PLAY, 0xFFFF)

/* Port to connect to */
#define TCP_PORT 44252

typedef struct
{
    uint8_t sig;
    uint16_t val;
} Packet_Desig_t;

typedef struct
{
    Packet_Desig_t designator;
    uint32_t size;
} Packet_Header_t;

#endif