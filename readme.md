# A Simple homemade, homegrown practice program for the Cyberpatriots compettion

Title says it all really. Since I was starting [Cyber Patriots](https://www.uscyberpatriot.org/) at my school, I decided fuck it, "Why not make my own practice software I could possibly use as my own version of cypat later on?", and so here we are, writing it. Let's just pray copyright isn't an issue for us.

## Description of function

Basically, it sets up scoring for a preset up image using a system based on a single "guidefile" for instructions on how to manage it.
The program is going to be as efficent and fast as possible, running in the background at all times.
It should be possible to compile with LLVM, GCC, with make, and python to automate the process. It will be primarily designed for Windows 11, Windows 10, Windows Server, Debian, Ubuntu, and their server varients primarily, with compatibility with Windows 7, Arch and it's derivatives, [FreeBSD](https://www.freebsd.org/), [OpenBSD](https://www.openbsdfoundation.org/), and various common Linux distros, thought the competion only uses Windows 10, Windows Server, Ubuntu, and [CISCO](https://www.cisco.com/c/en/us/products/ios-nx-os-software/index.html) (which I don't know shit about to be quite honest).
For each of these, it should contain an install script to make life easier for whoever is designing an image.
In any and all cases, [SHA-256](https://en.wikipedia.org/wiki/SHA-2) should be used for hashing, unless a reason for using [MD5](https://en.wikipedia.org/wiki/MD5) instead is found, and is completely solid.
At some point we will need to make a program to write guidefiles.

## Prerequisites

### Developing and compiling

- A C compiler and standard library for your target platform
    - [Gnu MP (GMP)](https://gmplib.org/)
- Text editor
- Git and some internet connection
- A [CPython](https://en.wikipedia.org/wiki/CPython) compatible interpreter
> ***OR***
- (preferably GNU) make

### Installing

- A CPython compatible interpreter
- A network connection
- A read-write permanent filesystem
- Some method of obtaining a guidefile

### Running

- A network connection
- A read-write permanent filesystem
- A guidefile

## TODOs and shit

### High priority

- Write documention for any design choices, program explainations, etc.
    1. Finish guidefile docs
- Create/Finish guidefile logic
- Add in arguments and various modes
    1. Verbose
    2. Pause
    3. Debug
    4. Anonymous
- Create image integrity checks
    1. Add in hashing of all the 100% critical files at the start of the program
        1. Any config files we use
        2. Any executables we use
        3. Hash Record
    2. Add in checking hashes at the start of every run of the main loop
    3. Add in checks to see if log files have been deleted
- Implement pauses at the end of the main loop to avoid excessive CPU consumption
- Implement error checking
    1. `errno` and standard library errors
    2. Program errors
        1. `state.internalErrno` errors
        2. Dynamic error handling
- Add in an exit proccess
    1. Trigger for the exit process
    2. Transmit logs to server specified in guidefile over [TCP](https://en.wikipedia.org/wiki/Transmission_Control_Protocol)
    3. Close the program
    4. Shutdown the image
    5. Add prevention metric
- Finish start process
- Create proper network capabilities
    1. Client
    2. Server for later
- Implement proper cryptography
    1. Fix the SHA256 segfault
    2. Add MD5 incase we ever need quick, not completely secure hashing, most likely for network purposes.
- Create a server program

### Medium Priority

- Implement "companion programs"
    1. Guidefile creation program
    2. Score viewer
- Create build automation
    1. Python
- Create install scripts written in Python for cross compatibility
    1. Windows 11/10
    2. Windows Server
    3. Ubuntu and Ubuntu based
    4. Debian and Debian based
    5. Low priority OSes
        1. Arch and Arch-based
        2. Windows 7
        3. FreeBSD/OpenBSD
        4. Misc. Linux distros
- Create detailed score logging
- Regex for setting conditions and any other possible uses

### Low Priority

- Cryptography
    1. Switch to [ECDH](https://en.wikipedia.org/wiki/Elliptic-curve_Diffie%E2%80%93Hellman)
    2. [ChaCha](https://en.wikipedia.org/wiki/Salsa20#ChaCha_variant) as a possible alternative for [AES](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard)
- Optimization (not including obvious optimizations while writing code)
