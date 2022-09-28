# Guide Files

Guide files are files that define the scoring for each image. They follow a specific format.

## Format

### Header

Each file starts with a header section, including data such as the number of conditions. \
\
The header can be described with the following struct:

```C
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
    uint16_t varCount;
} GF_Header_t;
```

### Variables

Variables are not baked into the guidefile, instead they are allocated by the program regulating the image. They are each 32 bit signed integers. They will be specified in code with the following typedef:

```C
typedef int32_t variable_t, var_t;
```

### Conditions

Conditions are the main portion of a guide file, and easily the most complex. They determine the way the scoring will behave on an image. \
 \
Conditions start with a small header described with the following struct:

```C
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
    *   0x05 for setting enabled
    *   0x06 for OS version
    *   0xFF for metacondition
    *   0xFE for initcondition
    */
    char typeCode;
} COND_Header_t;
```

Conditions contain a main body as well, each varying based on the condition type.

#### Metaconditions

Perhaps the simplest form of condition. It simply is based on the state of a certain variable, or variables. Each metacondition can be described with the following structs:

```C
typedef struct
{
    /* Value stored in the variable*/
    variable_t val;
    /* Variable code */
    uint16_t varCode;
} COND_var_t;

typedef struct
{
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
        }
        int32_t score;
    }
} COND_effect_t;

typedef struct
{
    COND_effect_t effect;
    /* Number of variables */
    uint16_t varCount;
    /* Not actual valid struct code, but whatever */
    COND_var_t vars[varCount];
} COND_Metacond_t;
```

#### Initconditions

Similar to metaconditions in structure, however they vastly different in function. Initconditions are run at the start of the program, and set the values of certain variables. They can be described with the following struct:

```C
typedef struct
{
    /* Number of variables */
    uint16_t varCount;
    /* Not actual valid struct code, but whatever */
    COND_var_t vars[varCount];
} COND_Initcond_t;
```

#### File exists/state condition

These conditions are more complex in nature, however, they are far more useful than initconditions and metaconditions. File state is, for the time being, simply another word for hash. File state conditions can be represented with the following struct:

```C
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
```
