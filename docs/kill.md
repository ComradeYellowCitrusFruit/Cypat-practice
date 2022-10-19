# Program exit methods

There are four methods by which the program can exit, `fatalError()`, `disgracefulExit()`, `gracefulExit()`, and `sleep()`.
`fatalError()` in case a fatal error occurs, and is not a result of foul play.
`disgracefulExit()` in case of foul play, hence why it is disgraceful, even though the process is perhaps the most graceful, in a technical sense, of them all.
`gracefulExit()` in case of an exit being triggered by a user.
`sleep()` in case of a temporary exit within the program, so that the image can be left, and then resumed afterwards.

## sleep()

`sleep()` is fairly simple, though perhaps the longest of the exit functions to run.
`sleep()` first collects all of the variables and `gf_state` into a single buffer, which is then hashed and recorded in the sleep file, with the said hash appended to it.
A null hash is then written to the end of the file, and the file is then hash, said hash is then put in place instead of the null one.
The score and sleep files are closed, and so is the sleep log.
Sleep then calls `createRecord()`.
Then the score is saved, `finiLog()` is called, and then all of the files are closed using `fcloseall()`.
The image is then terminated.

## gracefulExit()

`gracefulExit()` is more complex than sleep.
Integrity checks are made first.
A connection to the server specified in `gf_state.header.serverIP` is made.
Then, some data and log files are sent, in the following order.

1. `gf_state.score`
2. Log
3. Error log
4. Score log

The connection to the server is cut.
The noboot/don't boot file is created.
Then, `finiLog()` is called, and then all of the files are closed using `fcloseall()`.
Finally, the image is then terminated.

## disgracefulExit()

`disgracefulExit()` is not complex.
A connection to the server specified in `gf_state.header.serverIP` is made, but only a single packet is sent.
The packet contains a small amount of data telling the server that foul play has occured.
After that the connection to the server is cut.
The noboot/don't boot file is created.
Then, `finiLog()` is called, and then all of the files are closed using `fcloseall()`.
Finally, the image is then terminated.

## fatalError()

`fatalError()` is very simple.
It takes a single parameter, a `bool` called `permanant`.
If `permanant` is true, then the noboot/don't boot file is created.
The image is terminated.
