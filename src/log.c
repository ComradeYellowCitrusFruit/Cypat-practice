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

#define GENERATE_DATE_SIZE(tm) snprintf(NULL, 0, "%d-%02d-%02d %02d:%02d:%02d: ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec)
#define GENERATE_DATE(str, tm) sprintf(str, "%d-%02d-%02d %02d:%02d:%02d: ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec)

static inline void printDate(FILE *which)
{
    /* Get the time and convert it to UTC for obvious reasons. */
    time_t ltime;
    time(&ltime);
    struct tm timeinfo = *gmtime(&ltime);
    /* Print that shit to the file */
    char *date = malloc(GENERATE_DATE_SIZE(timeinfo));
    GENERATE_DATE(date, timeinfo);
    fprintf(which, date);
    /* Can't be having memory leaks */
    free(date);
    return;
}

void initLog()
{
    #ifdef _WIN32

    CreateDirectory(LOGPATH, NULL);

    #endif

    logFile = fopen(LOGPATH"/CYPAT.log", "a+");
    errLogFile = fopen(LOGPATH"/CYPAT.err.log", "a+");

    printDate(logFile);
    fprintf(logFile, "Logging initiated.\n");
    return;
}

void log(char *msg, ...)
{
    va_list args;
    va_start(args, msg);
    printDate(logFile);
    vfprintf(logFile, msg, args);
    va_end(args);
    return;
}

void errLog(char *errMsg, uint32_t errCode, ...)
{
    char *trueErrMsg;
    va_list args;
    va_start(args, errCode);
    trueErrMsg = malloc(vsnprintf(NULL, 0, errMsg, args));
    vsprintf(trueErrMsg, errMsg, args);
    printDate(logFile);
    fprintf(logFile, "An error has occured. Error code = %"PRIu32", errno = %zu, Error message: %s \n", errCode, (size_t)errno, trueErrMsg);
    printDate(errLogFile);
    fprintf(errLogFile, "An error has occured. Error code = %"PRIu32", errno = %zu, Error message: %s \n", errCode, (size_t)errno, trueErrMsg);
    va_end(args);

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

void finiLog()
{
    log("finiLog()");
    fclose(errLogFile);
    log("Error log closed. Closing main log");
    fclose(logFile);
    return;
}