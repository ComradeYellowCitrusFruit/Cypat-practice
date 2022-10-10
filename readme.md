# A Simple homemade, homegrown practice program for the Cyberpatriots compettion

Title says it all really. Since I am starting cypat at my school, I decided fuck it, "Why not make my own practice software I could possibly use as my own version of cypat later on?", and so here we are, writing it. Let's just pray copyright isn't an issue for us.

## Description of function

Basically, it sets up scoring for a preset up image using a system based on a single "guidefile" for instructions on how to manage it.
The program is going to be as efficent and fast as possible, running in the background at all times.
It should be possible to compile with LLVM, GCC, and MSVC, with make, and python to automate the process. It will be primarily designed for Windows 11, Windows 10, Windows Server, Debian, Ubuntu, and their server varients primarily, with compatibility with Windows 7, Arch and it's derivatives, FreeBSD, OpenBSD, and various common Linux distros, thought the competion only uses Windows 10, Windows Server, Ubuntu, and CISCO (which I don't know shit about to be quite honest).
For each of these, it should contain an install script to make life easier for whoever is designing an image.
In any and all cases, SHA-256 should be used for hashing, unless a reason for using MD5 instead is found, and is completely solid.
At some point we will need to make a program to write guidefiles.

At the moment, MSVC compatibility has been effectively removed for the time being because we are using GMP for our Diffie-Hellman implementation.
We will have to get ourselves an alternative for GMP for use with MSVC or cut out MSVC entirely, however with the recently written makefile, it would be easier to cut out MSVC.

## Prerequisites

### Developing and compiling

- A C compiler and standard library for your target platform
- A CPython compatible interpreter
- (preferably GNU) make
- Text editor
- Git and some internet connection

### Installing and running

- A CPython compatible interpreter
- A network connection and driver
- A read-write permanent filesystem and driver
- Some method of obtaining a guidefile

## TODOs and shit

- Finish guidefile docs
- Create/Finish guidefile logic
- Create image integrity checks
    1. Add hashes into guidefiles
    2. Add in hashing of all the 100% critical files at the start of the program
    3. Add in checking hashes at the start of every run of the main loop
    4. Add in checks to see if log files have been deleted
- Implement pauses at the end of the main loop to avoid excessive CPU consumption
- Implement error checking
    1. `errno` and standard library errors
    2. Program errors
- Add in an exit proccess
    1. Trigger for the exit process
    2. Transmit logs to server specified in guidefile over TCP
    3. Close the program
    4. Shutdown the image
    5. Add prevention metric
- Add in a sleep process
    1. Log the sleep
    2. Save the score
    3. Indicate sleep somewhere
    4. Shutdown the image
- Finish start process
    1. Initalize logging
    2. Open necessary files
    3. Initalize gf_state
    4. Detect if sleep has occurred
    5. If it's the first time running
        1. Register 32 bit unique ID with the server specified in the guidefile
        2. Create ID file
- Implement "companion programs"
    1. Guidefile creation program
    2. Score viewer
    3. Server program
- Create build automation
    1. (GNU) make
    2. Python
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
- Create proper network capabilities
    1. Client
    2. Server for later
    3. Diffie-Hellman for session key creation and exchange.
- Implement proper cryptography
    1. SHA256 for hashing.
    2. Diffie-Hellman for session key creation and exchange.
       - Later on it may be benefitional to switch to ECDH, however regular Diffie-Hellman will suffice
    3. AES for encryption.
    4. ChaCha as a possible alternative for AES
    5. MD5 incase we ever need quick, not completely secure hashing, most likely for network purposes.
