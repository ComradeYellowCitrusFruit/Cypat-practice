#ifndef GUIDEFILES_H
#define GUIDEFILES_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct
{
    /* Condition start offset */
    int32_t offset;
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
    *   ox05 for another Linux distribution
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
    int32_t time;
    /* IPv4 or IPv6 */
    bool IPv4;
    /* IP of server to connect to, IP should be in utf-8 or ascii, null terminating, port is 44252. */
    char serverIP[255];
    /* Number of variables, primarily for metaconditions */
    uint16_t varCount;
} GF_Header_t;
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