#include <stdio.h>
#include <stdlib.h>
#include "include/eventLoop.h"
#include "include/log.h"

#ifdef _WIN32
/* I fucking hate windows */
#include <Windows.h>
#define MAIN int Main()
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdParam, int iCmdShow)
{
    Main();
}
#elif defined(__unix__)
#include <unistd.h>
#include <signal.h>

#define MAIN int main()

/* Self explanitory */
static inline void daemonize()
{
    /* I do not understand this code, and I pray I don't have to */
    pid_t pid;
    pid = fork();

    if(pid < 0)
        exit(1);
    
    if(setsid() < 0)
        exit(0);

    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    pid = fork();

    if (pid < 0)
        exit(1);
    if (pid > 0)
        exit(0);
    
    umask(0);
    chdir("/");
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
    {
        close (x);
    }
}
#endif

MAIN
{
    #ifdef __unix__
    /* Daemonize this shit */
    daemonize();
    #endif
    /* Start logging */
    initLog();
    /* Log this shit */
    log("Process daemonized.");
    /* And we are done here let's book it. */
    enterLoop();
}