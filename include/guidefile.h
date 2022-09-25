#ifndef GUIDEFILES_H
#define GUIDEFILES_H

#include <stdint.h>

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
    /* IP/DNS to send the finished logs and score too, UTF-8 and ASCII only */
    char result_IPoDNS[255];
    /* Number of variables, primarily for metaconditions */
    uint16_t varCount : 12;
} GF_Header_t;

typedef struct
{
    GF_Header_t header;
    int32_t *vars;
    int32_t *score;
} GF_STATE_T;


#endif