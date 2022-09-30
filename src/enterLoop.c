#ifdef __unix__
#include <unistd.h>
#elif defined(_WIN32)
#endif
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "include/eventLoop.h"
#include "include/log.h"
#include "include/guidefile.h"
#include "include/errors.h"

extern uint8_t majorVer;
extern uint8_t minorVer;
extern uint8_t patch;

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
    if(gf_state.header.majorVer != majorVer)
    {
        errLog("gf_state.header.majorVer == %"PRIu8", not %"PRIu8, INCOMPATIBLE_MAJOR_VER, gf_state.header.majorVer, majorVer);
    }
    else if(gf_state.header.minorVer != minorVer)
    {
        errLog("gf_state.header.minorVer == %"PRIu8", not %"PRIu8, INCOMPATIBLE_MINOR_VER, gf_state.header.minorVer, minorVer);
    }
    /* Oh boy an infinite loop*/
    while(1)
        if(mainLoop() == 0) break;
    killLoop();
}