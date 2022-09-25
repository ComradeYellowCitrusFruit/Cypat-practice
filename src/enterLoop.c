#ifdef __unix__
#include <unistd.h>
#elif defined(_WIN32)
#endif
#include <stdio.h>
#include "include/eventLoop.h"
#include "include/log.h"
#include "include/guidefile.h"

/* Enter the main event loop. Not that complex. */
NORETURN void enterLoop()
{
    log("enterLoop()");
    fscore = fopen(scoreFilePath, "r+");
    log("Score file opened");
    scoreLog = fopen(scoreLogPath, "a+");
    log("Score log opened");
    guideFile = fopen(guideFilePath, "r");
    log("Guidefile oppened");
    initState(guideFile);
    /* Oh boy an infinite loop*/
    while(1)
        if(mainLoop() == 0) break;
    killLoop();
}