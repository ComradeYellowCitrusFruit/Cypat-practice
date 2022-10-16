# The Start up process

## Windows entry point

On Windows, the program uses WinMain() for the entry point. From there, it simply starts without setting up a window, then straight away initializes logging, and jumps to enterLoop(). This is one of the rare times Windows is faster than unix-based systems. 

## Unix-based entry point

On unix-based systems, the program uses the traditional main() for the entry point. From there, it follows standard daemonization process, via daemonize(). Then, it calls initLog() and jumps to enterLoop().

## enterLoop()

enterLoop() starts by checking for the don't boot file, and the sleep file. If the sleep file is found, then sleep is flagged and the hash record is loaded. Integrity checks are made, if any of them fail, the program is terminated via fatalErr(). Then opening the score file, then the score log, it then opens the guidefile. From there, it calls initState(), to initalize gf_state. Versions are checked, and if they don't match up, the program is terminated via fatalErr(). Any configuration files are loaded and approprate flags are set. At this point the start up process is finished, and the infinite loop of mainLoop() is started.
