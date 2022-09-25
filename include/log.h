#ifndef LOG_H
#define LOG_H

extern char *LogPath;

void initLog();
/* Log a message, works just like printf. */
void log(char *msg, ...);
/* Log an error, logs to a specific file as well as the general log file, it logs errno, the errCode, and the errMsg, which is a string formated just like printf. */
void errLog(char *errMsg, int errCode, ...);

#endif