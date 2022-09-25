#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include <stdio.h>

#ifdef _GNUC_
#define NORETURN __attribute__((noreturn))
#elif defined(_MSC_VER)
#define NORETURN __declspec(noreturn)
#endif

/* Score file. */
extern FILE *fscore;
/* Score log. */
extern FILE *scoreLog;
/* Score. */
extern int score;

/* The file that governs over the scoring for the image. */
extern FILE *guideFile;

#ifdef __unix__
extern char scoreFilePath[];
extern char scoreLogPath[];
extern char guideFilePath[];
#elif defined(_WIN32)
extern char scoreFilePath[];
extern char scoreLogPath[];
extern char guideFilePath[] ;
#endif

/* Enter the main event loop. Not that complex. */
NORETURN void enterLoop();
/* Self explanitory */
int mainLoop();
/* End the loop and exit the program, shutdown the virtual image, and create the launch prevention file. */
NORETURN void killLoop();

#endif