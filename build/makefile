# Define our vars
incdir := ../
srcdir := ../src/
bindir := ../bin/
cryptsrc := ../src/crypt/

# Our default compilers
cc := gcc
cxx := g++

# Default, compiler based, compiler args
CFLAGS := -I$(incdir) -O2 -Wall -pedantic -ansi 
CXXFLAGS := $(CFLAGS)

objects := enterloop.o eventLoop_vars.o guidefile.o initconds.o log.o mainLoop.o start.o

# The cryptography files need to be done seperately from the rest of the object files

# Diffie-Hellman as a single object file
DH.o: $(cryptsrc)DH/init.cpp $(cryptsrc)DH/secret.cpp $(cryptsrc)DH/getptr.cpp 
	$(cxx) $(CXXFLAGS) -c $^ -o $(bindir)$@

rand.o: $(cryptsrc)rand.c
	$(cc) $(CFLAGS) -c $< -o $(bindir)$@

SHA256.o: $(cryptsrc)SHA256.c 
	$(cc) $(CFLAGS) -c $< -o $(bindir)$@

AES.o: $(cryptsrc)AES/AES.c $(cryptsrc)AES/counter.c
	$(cc) $(CFLAGS) -c $^ -o $(bindir)$@

log.o: $(srcdir)log.c
	$(cc) $(CFLAGS) -c $< -o $(bindir)$@

eventLoop.o: $(srcdir)mainLoop.c $(srcdir)enterloop.c $(srcdir)eventLoop_vars.c 
	$(cc) $(CFLAGS) -c $^ -o $(bindir)$@

conditions.o: $(srcdir)fstateconds.c $(srcdir)initconds.c $(srcdir)metaconds.c $(srcdir)settingscond.c
	$(cc) $(CFLAGS) -c $^ -o $(bindir)$@

guidefiles.o: $(srcdir)guidefile.c $(srcdir)gfVerify.c
	$(cc) $(CFLAGS) -c $^ -o $(bindir)$@

kill.o: $(srcdir)sleep.c
	$(cc) $(CFLAGS) -c $^ -o $(bindir)$@

isqrt.o: $(srcdir)isqrt.c
	$(cc) $(CFLAGS) -c $< -o $(bindir)$@