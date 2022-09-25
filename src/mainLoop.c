#ifdef __unix__
#include <unistd.h>
#elif _WIN32
#include <Windows.h>
#endif
#include <stdlib.h>
#include "include/eventLoop.h"
#include "include/log.h"

/* Self explanitory */
int mainLoop()
{
    log("mainLoop()");
    /* Code goes here */
}