# Arguments

## Passing arguments

Unlike a typical program, we can't rely on typical console arguments, however, we will still likely need arguments at some point, so we have to use a static file for them.
What would be `argv[0]` will not be present in this file, as we will not need it.
Other than that, our arguments will be identical to typical console ones.

## List of all arguments

There are quite a number of arguments. Probably most useful is `-v` or `--verbose`. Here is the full list, effects, short, and full.

1. Verbose mode. Short: `-v`. Full: `--verbose`, `--verbose-mode`. Effects: Enables verbose logging.
2. Use notifications. Short: `-n`. Full: `--notify`, `--notifications`. Effects: Allows the program to use notifications to notify the user about score updates.
3. Debug mode. Short: `-d`. Full: `--debug`, `--debug-mode`. Effects: Enables debug mode
4. Change pause time. Short: `-p ${duration}`. Full: `--pause ${duration}`. Effects: Changes the duration of the pauses at the end of the main loop, in milliseconds, default is 50ms.
5. Anonymous mode. Short: `-a`. Full: `--anon`, `--anonymous`. Effects: Enables anonymous mode, which tells the program to never trigger login popups, and anonymously log into the server whenever necessary.
6. Use `alloca()`. Short: `-A`. Full: `--alloca`, `--enable-alloca`. Effects: Allows the program to use `alloca()`, must be used with debug mode.
