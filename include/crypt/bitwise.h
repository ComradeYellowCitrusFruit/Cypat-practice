#ifndef CRYPT_BITWISE_OPS_H
#define CRYPT_BITWISE_OPS_H

#include <stdint.H>

static uint16_t rotl8(uint8_t rot, uint8_t by)
{
    return (rot << by) | (rot >> (16 - by));
}

static uint16_t rotr8(uint8_t rot, uint8_t by)
{
    return (rot >> by) | (rot << (8 - by));
}

static uint16_t rotl16(uint16_t rot, uint16_t by)
{
    return (rot << by) | (rot >> (16 - by));
}

static uint16_t rotr16(uint16_t rot, uint16_t by)
{
    return (rot >> by) | (rot << (16 - by));
}

static uint32_t rotl32(uint32_t rot, uint32_t by)
{
    return (rot << by) | (rot >> (32 - by));
}

static uint64_t rotr32(uint32_t rot, uint32_t by)
{
    return (rot >> by) | (rot << (32 - by));
}

static uint64_t rotl64(uint64_t rot, uint64_t by)
{
    return (rot << by) | (rot >> (64 - by));
}

static uint64_t rotr64(uint64_t rot, uint64_t by)
{
    return (rot >> by) | (rot << (64 - by));
}

#endif