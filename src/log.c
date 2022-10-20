#ifdef __unix__
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#elif defined(_WIN32)
/* I fucking hate windows. */
#include <Windows.h>
#endif
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <inttypes.h>
#include "include/log.h"
#include "include/errors.h"
#include "include/state.h"

FILE *logFile;
FILE *errLogFile;
FILE *debugLogFile;
FILE *networkLogFile;

void initLog()
{
    #ifdef _WIN32

    CreateDirectory(LOGPATH, NULL);

    #endif

    logFile = fopen(LOGPATH"/CYPAT.log", "a+");
    errLogFile = fopen(LOGPATH"/CYPAT.err.log", "a+");
    if(state.args.debug)
        debugLogFile = fopen(LOGPATH"/CYPAT.debug.log", "a+");
    networkLogFile = fopen(LOGPATH"/CYPAT.network.log", "a+");

    printDate(logFile);
    fprintf(logFile, "Logging initiated.\n");
    return;
}

void log(char *msg, ...)
{
    /* Get the args together */
    va_list args;
    va_start(args, msg);

    /* Get the current time */
    time_t Time;
    time(&time);
    
    /* Print the log information */
    fprintf(logFile, "%d %d %zu ", GENERAL, INFORMATIONAL, (size_t)Time);

    /* Print the log message, formated and all. */
    vfprintf(logFile, msg, args);
    fprintf(logFile, "\n");
    return;
}

/* Log an error, logs to a specific file as well as the general log file, it logs errno, the errCode, and the errMsg, which is a string formated just like printf. */
void errLog(char *errMsg, int urgency, uint32_t errCode, ...)
{
    /* Set up the args */
    va_list args;
    va_start(args, errCode);

    /* Get the current time */
    time_t Time;
    time(&time);

    /* Print to the main log file */

    /* Print the log information */
    fprintf(logFile, "%d %d %zu %"PRIu32"x ", ERROR, urgency, (size_t)Time, errCode);

    /* Print the log message, formated and all. */
    vfprintf(logFile, errMsg, args);
    fprintf(logFile, "\n");

    /* Print to the error log file */

    /* Print the log information */
    fprintf(errLogFile, "%d %d %zu %"PRIu32"x ", ERROR, urgency, (size_t)Time, errCode);

    /* Print the log message, formated and all. */
    vfprintf(errLogFile, errMsg, args);
    fprintf(errLogFile, "\n");

    switch(errCode)
    {
        case CPU_32BITS:
            break;
        case CPU_AES_EXTENSIONS_UNAVALIBLE:
            break;
        case CPU_NOT_X86:
            break;
        default:
            state.internalErrno = errCode;
            break;
    }
    return;
}

/* Log a message if debug is true, functions like log() otherwise */
void debugLog(char *msg, ...)
{
    if(state.args.debug)
    {
        /* Get the args together */
        va_list args;
        va_start(args, msg);

        /* Get the current time */
        time_t Time;
        time(&time);
    
        /* Print to the main log file */

        /* Print the log information */
        fprintf(logFile, "%d %d %zu ", DEBUG, INFORMATIONAL, (size_t)Time);

        /* Print the log message, formated and all. */
        vfprintf(logFile, msg, args);
        fprintf(logFile, "\n");

        /* Print to the debug log file */

        /* Print the log information */
        fprintf(debugLogFile, "%d %d %zu ", DEBUG, INFORMATIONAL, (size_t)Time);

        /* Print the log message, formated and all. */
        vfprintf(debugLogFile, msg, args);
        fprintf(debugLogFile, "\n");
    }
    return;
}

void finiLog()
{
    log("finiLog()");
    fclose(errLogFile);
    log("Error log closed. Closing main log");
    fclose(logFile);
    return;
}