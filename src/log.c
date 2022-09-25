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
#include "include/log.h"

FILE *logFile;
FILE *errLogFile;
/* Fuck it define them both I hate preprocessor directives */
#define LOGPATH_U "/var/log"
#define LOGPATH_W "C:/CYPAT_logs" 

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
    /* Idk where else to put logs on Windows */
    CreateDirectory(LOGPATH_W, NULL);
    LogPath = LOGPATH_W;
    /* Purely for string concatination shit I swear */
    #define CORRECTLOGPATH LOGPATH_W
    #elif defined(__unix__)
    /* Unix based systems prove themselves better than Windows once again */
    LogPath = LOGPATH_U;
    /* Purely for string concatination shit I swear */
    #define CORRECTLOGPATH LOGPATH_U
    #endif
    logFile = fopen(CORRECTLOGPATH"/CYPAT.log", "a+");
    errLogFile = fopen(CORRECTLOGPATH"/CYPAT.err.log", "a+");
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
void errLog(char *errMsg, int errCode, ...)
{
    char *trueErrMsg;
    va_list args;
    va_start(args, errCode);
    trueErrMsg = malloc(vsnprintf(NULL, 0, errMsg, args));
    vsprintf(trueErrMsg, errMsg, args);
    printDate(logFile);
    fprintf(logFile, "An error has occured. Error code = %d, errno = %d, Error message: %s \n", errCode, errno, trueErrMsg);
    printDate(errLogFile);
    fprintf(errLogFile, "An error has occured. Error code = %d, errno = %d, Error message: %s \n", errCode, errno, trueErrMsg);
    va_end(args);
    return;
}