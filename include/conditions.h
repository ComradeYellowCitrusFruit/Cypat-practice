#ifndef CONDITIONS_H
#define CONDITIONS_H

#include <stdint.h>
#include <stdbool.h>
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
    /*  True for var
    *   False for score
    */
    bool varOrScore;
    union
    {
        struct
        {
            COND_var_t var;
            /*  Effect to apply to var[varCode]
            *   0xFF Set too
            *   0x01 Add
            *   0x02 Subtract
            *   0x03 Multiply
            *   0x04 Divide
            *   0x10 Bitwise or
            *   0x11 Bitwise and
            *   0x12 Bitwise xor
            *   0x13 Bitwise not
            *   0x14 Bitwise lshift
            *   0x15 Bitwise rshift
            *   0x16 Bitwise nand
            *   0x17 Bitwise nor
            *   0x20 To the power of
            *   0x21 To the root of
            */
            char effect;
        };
        int32_t score;
    };
} COND_effect_t;

typedef struct
{
    COND_effect_t effect;
    /* Number of variables */
    uint16_t varCount;
} COND_Metacond_t;

typedef struct
{
    /* Number of variables */
    uint16_t varCount;
} COND_Initcond_t;

typedef struct
{
    /* Offset at which the name, a null terminated string, starts. */
    int32_t nameOffset;
    /* Are we checking the state, or existence? */
    bool existsOrState;
    /* File hash */
    uint8_t hash[32];
    /* Which triggers the outcome, exists or not? */
    bool existsOrNot;
    /* Effect */
    COND_effect_t effect;
} COND_fstate_t;

typedef struct
{
    /* Offset at which the command, a null terminated string, starts. */
    uint32_t commandOffset;
    /* Result hash */
    uint8_t hash[32];
    /* Effect */
    COND_effect_t effect;
} COND_cresult_t;

typedef struct
{
    /* Result hash */
    uint8_t hash[32];
    /* Effect */
    COND_effect_t effect;
} COND_OSVER_t;

typedef struct
{
    /* Offset to the setting string*/
    uint32_t settingOffset;
    /* Offset to the file name string*/
    uint32_t fnameOffset;
    /* Effect */
    COND_effect_t effect;
} COND_SETTING_t;

typedef struct
{
    /* Offset to the app. string */
    uint32_t appOffset;
    /* Effect */
    COND_effect_t effect;
} COND_APPINSTALL_t;

void runInitConds();

#endif