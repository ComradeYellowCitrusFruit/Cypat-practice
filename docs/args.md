# Arguments

## Passing arguments

Unlike a typical program, we can't rely on typical console arguments, however, we will still likely need arguments at some point, so we have to use a static file for them.
What would be `argv[0]` will not be present in this file, as we will not need it.
Other than that, our arguments will be identical to typical console ones.

## List of all arguments

There are quite a number of arguments. Probably most useful is `-v` or `--verbose`. Here is the full list, effects, short, and full.

1. Verbose mode. Short: `-v`. Full: `--verbose`, `--verbose-mode`. Effects: Enables verbose logging.
2. Use notifications. Short: `-n`. Full: `--notify`, `--notifications`. Effects: Allows the program to use notifications to notify the user about score updates.
3. Debug mode. Short: `-d`. Full: `--debug`, `--debug-mode`. Effects: Enables debug mode, implies verbose mode.
4. Change pause time. Short: `-p${duration}`. Full: `--pause-time=${duration}`. Effects: Changes the duration of the pauses at the end of the main loop, in milliseconds, default is 50ms.
5. Anonymous mode. Short: `-a`. Full: `--anon`, `--anonymous`. Effects: Enables anonymous mode, which tells the program to never trigger login popups, and anonymously log into the server whenever necessary.
6. Use `alloca()`. Short: `-A`. Full: `--alloca`, `--enable-alloca`. Effects: Allows the program to use `alloca()`, must be used with debug mode.
7. Slow mode. Short: `-s`. Full: `--slow`, `--slow-mode`. Effects: Enables slow mode, which tells the program that it can function more securely and with more anti-cheating precautions, implied with the use of debug mode.
8. Fast mode. Short: `-f`. Full: `--fast`, `--fast-mode`. Effects: Enables fast mode, which tells the program that it can use more optimizations, and experimental ones as well. Dissables slow mode.
9. Experimental mode. Short: `-e`. Full: `--experimental`, `--experimental-mode`. Effects: Enables experimental features, implies use of `alloca()` without debug mode.
