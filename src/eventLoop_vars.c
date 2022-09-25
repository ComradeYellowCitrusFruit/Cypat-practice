#include <stdio.h>
#include <stdint.h>
#include "include/eventLoop.h"

/* Score file. */
FILE *fscore;
/* Score log. */
FILE *scoreLog;
/* Score. */
int32_t score;

/* The file that governs over the scoring for the image. */
FILE *guideFile;

#ifdef __unix__
char scoreFilePath[] = "/CYPAT/SCORE";
char scoreLogPath[] = "/CYPAT/SCORE_LOG";
char guideFilePath[] = "/CYPAT/GUIDEFILE";
#elif defined(_WIN32)
char scoreFilePath[] = "C:/CYPAT/SCORE";
char scoreLogPath[] = "C:/CYPAT/SCORE_LOG";
char guideFilePath[] = "C:/CYPAT/GUIDEFILE";
#endif