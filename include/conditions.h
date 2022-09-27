#ifndef CONDITIONS_H
#define CONDITIONS_H

#include "include/guidefile.h"

typedef struct
{
    /* Offset to next condition */
    int nextOffset;
    /* Size of condition in bytes */
    int condSize;
    /* Offset to prev. condition */
    int prevOffset;
    /*  Code for the type of condition
    *   0x00 for file exists
    *   0x01 for directory exists
    *   0x02 for forensics
    *   0x03 for app. installed
    *   0x04 for command results
    *   0x05 for OS version
    *   0xFF for metacondition
    *   0xFE for initcondition
    */
    char typeCode;
} COND_Header_t;

typedef struct
{
    /* Value stored in the variable*/
    variable_t val;
    /* Variable code */
    uint16_t varCode;
} COND_var_t;

typedef struct
{
    int32_t scoreVal;
    /* Number of variables */
    uint16_t varCount;
} COND_Metacond_t;

typedef struct
{
    /* Number of variables */
    uint16_t varCount;
} COND_Initcond_t;

void runInitConds();

#endif