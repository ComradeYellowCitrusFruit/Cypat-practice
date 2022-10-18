# Error code definitions

## Parts

The most significant byte of each error code is significant, determining what the error code is for.

    0x00 - General, no specific module or functional category
    0x80 - Networking module and functions, also includes Diffie-Hellman
    0xC0 - Memory allocation and management
    0xE0 - Filesystem, not including guidefiles
    0xF0 - Guidefiles and conditions
    0xF8 - Cpu and hardware info

The middle 2 bytes of each error code tell if it's fatal, or not.

    0xFFFF - Fatal
    Anything else - Not fatal

The least significant byte of each error code is insignificant, they hold no meaning.

## Naming convientions

The name of the error code should be very esentially just the meaning of the error code.
Each error code should have a prefix directly relating to the most significant byte.

    CPU_ - 0xF8
    GUIDEFILE_ - 0xF0
    FILESYSTEM_ - 0xE0
    MALLOC_, CALLOC_, ALLOCA_, or MEMORY_ - 0xC0
    NETWORK_, or DIFFIEHELLMAN_ - 0x80
    GENERAL_ - 0x00

## Unofficial value convientions

Error codes often contain small, three character ASCII strings within them.
Two good examples of this would be CPU_NOT_X86 and CPU_AES_EXTENSIONS_UNAVALIBLE.
Many other times, they contain ASCII strings compressed into 24bit or 8bit forms.
Two good examples of this would be CPU_IMPOSSIBLE_EVENT_OCCURED and ALLOCA_UNAVALIBLE.
Unless it is absolutely impossible, the value should be related to the name of the error code.
