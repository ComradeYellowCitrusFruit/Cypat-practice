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
    uint32_t offset;
    /* Footer offset */
    uint32_t foffset;
    /* File size */
    uint32_t size;
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
    *   0x05 for another Linux distribution
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
    uint32_t time;
    /* IPv4 or IPv6 */
    bool IPv4;
    /* IP of server to connect to, IP should be in utf-8 or ascii, null terminating, port is 44252. */
    char serverIP[255];
    /* Number of variables, primarily for metaconditions */
    uint16_t varCount;
    /* Guidefile hash, to confirm validity. */
    uint8_t hash[32];
} GF_Header_t;
```

### Footer

Each guidefile ends with a footer, put in place for validation purposes. They can be represented with the following struct:

```C
typedef struct
{
    /* Condition start offset */
    uint32_t offset;
    /* Header offset */
    uint32_t hoffset;
    /* File size */
    uint32_t size;
    /* Guidefile hash, to confirm validity. */
    uint8_t hash[32];
} GF_Footer_t;
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
    uint32_t nextOffset;
    /* Size of condition in bytes */
    uint32_t condSize;
    /* Offset to prev. condition */
    uint32_t prevOffset;
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

These conditions are more complex in nature, however, they are far more useful than initconditions and metaconditions. File state is, for the time being, simply another word for hash. Forensics conditions are simply another phrase for these. File state conditions can be represented with the following struct:

```C
typedef struct
{
    /* Offset at which the name, a null terminated string, starts. */
    uint32_t nameOffset;
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

#### Command result condition

Command result conditions are exactly like file state conditions, except with a change of struct member names. Command result conditions can be represented with the following struct:

```C
typedef struct
{
    /* Offset at which the command, a null terminated string, starts. */
    uint32_t commandOffset;
    /* Result hash */
    uint8_t hash[32];
    /* Effect */
    COND_effect_t effect;
} COND_cresult_t;
```

#### Operating system version condition

Operating system versions work differently on different operating systems. On Linux they work checking the kernel version, using `uname -srm > /tmp/CYPAT_COND` then checking the hash of /tmp/CYPAT_COND, if you need the version of the exact linux based operating system and not the kernel, you can use fstate conditions on the appropriate files. On Windows, they check for the operating system version using `systeminfo > C:/tmp/CYPAT_OSVER; grep "OS Version:" C:/tmp/CYPAT_OSVER > C:/tmp/CYPAT_COND` then checking the hash of C:/tmp/CYPAT_COND. They can be represented with the following struct:

```C
typedef struct
{
    /* Result hash */
    uint8_t hash[32];
    /* Effect */
    COND_effect_t effect;
} COND_OSVER_t;
```

#### Setting enabled condition

These conditions are meant to work based on OS settings, however, the name is a misnomer. They simply search for a string in a file. They can be represented with the following struct:
```C
typedef struct
{
    /* Offset to the setting string*/
    uint32_t settingOffset;
    /* Offset to the file name string*/
    uint32_t fnameOffset;
    /* Effect */
    COND_effect_t effect;
} COND_SETTING_t;
```

#### App. installed

Similarly to setting conditions, the name is a misnomer, they really check if a package is installed, on Linux and BSD anyway. However, on Windows, they do infact check if an app. is installed. They can be represented with the following struct:
```C
typedef struct
{
    /* Offset to the app. string */
    uint32_t appOffset;
    /* Effect */
    COND_effect_t effect;
}