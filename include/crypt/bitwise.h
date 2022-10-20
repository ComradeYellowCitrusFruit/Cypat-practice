/*
*
*   include/crypt/bitwise.h
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

#ifndef CRYPT_BITWISE_OPS_H
#define CRYPT_BITWISE_OPS_H

#include <stdint.H>

static inline uint8_t rotl8(uint8_t rot, uint8_t by)
{
    return (rot << by) | (rot >> (16 - by));
}

static inline uint8_t rotr8(uint8_t rot, uint8_t by)
{
    return (rot >> by) | (rot << (8 - by));
}

static inline uint16_t rotl16(uint16_t rot, uint16_t by)
{
    return (rot << by) | (rot >> (16 - by));
}

static inline uint16_t rotr16(uint16_t rot, uint16_t by)
{
    return (rot >> by) | (rot << (16 - by));
}

static inline uint32_t rotl32(uint32_t rot, uint32_t by)
{
    return (rot << by) | (rot >> (32 - by));
}

static inline uint32_t rotr32(uint32_t rot, uint32_t by)
{
    return (rot >> by) | (rot << (32 - by));
}

static inline uint64_t rotl64(uint64_t rot, uint64_t by)
{
    return (rot << by) | (rot >> (64 - by));
}

static inline uint64_t rotr64(uint64_t rot, uint64_t by)
{
    return (rot >> by) | (rot << (64 - by));
}

static inline uint8_t nibbleSwap(uint8_t byte)
{
    return (byte << 4) | (byte >> 4);
}

#endif