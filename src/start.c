/*
*
*   src/start.c
*   Originally written by Alicia Antó Valencía - https://github.com/ComradeYellowCitrusFruit
*
*   A collection of programs for cybersecurity competitions and practices
*   Copyright (C) 2022  Alicia Antó Valencía
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include <stdio.h>
#include <stdlib.h>
#include "include/eventLoop.h"
#include "include/log.h"

#ifdef _WIN32

/* I fucking hate windows */
#include <Windows.h>
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PSTR szCmdParam, int iCmdShow)
{
    /* Start logging */
    initLog();
    /* Log this shit */
    log("Windows process started.");
    /* And we are done here let's book it. */
    enterLoop();
}

#elif defined(__unix__)

#include <unistd.h>
#include <signal.h>

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

int main()
{
    /* Daemonize this shit */
    daemonize();
    /* Start logging */
    initLog();
    /* Log this shit */
    log("Process daemonized.");
    /* And we are done here let's book it. */
    enterLoop();
}
#endif