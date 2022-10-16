# Integrity checks and the hash record

## Integrity checks

Integrity checks are performed through checking hashes based off a cache in memory.
A file is hashed, then the hash is checked against the hash in memory, if they are the same, the program continues to run, and if they aren't the same, the program exits via `disgracefulExit()`.
This is all assuming it is occuring in `mainLoop()`.
If it occurs during `enterLoop()`, everything is the same, except `fatalErr()` is triggered, in place of `disgracefulExit()`.

## Hash record

The Hash Record is a file created by `sleep()`, it provides a cache that can be quickly loaded into memory instead of calculating all of the hashes.
At the end of the file, a hash of the hash record, but with said hash nulled out.
This hash can be used to verify the hash record.
If the hash record doesn't pass verification, the program exits via `disgracefulExit()` if it's in `mainLoop()`, if it's in start it will exit via `fatalErr()`.
