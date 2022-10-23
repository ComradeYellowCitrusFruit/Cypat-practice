# Logging

Logging is core to the function of the program. We will use our own log format for our logs.

## Log files

There are four log files, not including the score log, which is it's own thing. These are the main log, error log, debug log, and network log. The main log contains all of the log messages, and is the only file accessed with `log()`. The error log contains all error messages, and is accessed with `errLog()` and `netErrLog()`. The debug log contains any messages sent with `debugLog()`, and only exists if the arguments include debug mode. The network log contains messages sent with `netLog()` and `netErrLog()`.

## Log format

Our logs follow a simple format: \
`[LOG TYPE] [LOG URGENCY] [UNIX TIMESTAMP] {MESSAGE}` \
Error logs have their own little internal format for the message, as do network logs. \
The error log format is as follows: \
`[LOG TYPE] [LOG URGENCY] [UNIX TIMESTAMP] {[ERROR CODE] {MESSAGE}}` \
The netowrk log format is as follows: \
`[LOG TYPE] [LOG URGENCY] [UNIX TIMESTAMP] {(IF NECESSARY)[PACKET DESIGNATOR CODE] [(IF IT'S AN ERROR LOG) ERROR CODE] {MESSAGE}}`

There are 4 log types:

- General, value is 0, function is `log()`
- Error, value is 1, functions are `errLog()` and `netErrLog()`
- Network, value is 2, functions are `netLog()`
- Debug, value is 3, function is `debugLog()`

There are 5 log urgencies:

- Informational, value is 3
- Warning, value is 2
- Error, value is 1
- Live or die/critical, value is 0
- Fatal, value is -1

For a list of error codes and packet designators, see error.h and network.h respectively.
