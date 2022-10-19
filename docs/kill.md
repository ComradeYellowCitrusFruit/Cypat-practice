# Program exit methods

There are four methods by which the program can exit, `fatalError()`, `disgracefulExit()`, `gracefulExit()`, and `sleep()`.
`fatalError()` in case a fatal error occurs, and is not a result of foul play.
`disgracefulExit()` in case of foul play, hence why it is disgraceful, even though the process is perhaps the most graceful, in a technical sense, of them all.
`gracefulExit()` in case of an exit being triggered by a user.
`sleep()` in case of a temporary exit within the program, so that the image can be left, and then resumed afterwards.

## sleep()

Sleep is fairly simple, though perhaps the longest of the exit functions to run. `sleep()` first collects all of the variables and `gf_state` into a single buffer, which is then hashed and recorded in the sleep file, with the said hash appended to it. A null hash is then written to the end of the file, and the file is then hash, said hash is then put in place instead of the null one. Then the score is saved, `finiLog()` is called, and then all of the files are closed using `fcloseall()`. The image is then terminated.
