# Some explanation as to our choice of languages

This project is going to be exclusively C, with some C++ under some circumstances, currently only GMP/Diffie-Hellman related code, and possibly some inline assembly for optimizations.
Python will be primarily used for the build process, since it is decently easy to handle args, and is cross compatible. However, if we can't find an alternative solution instead of GMP for msvc, we will be able to use make and autotools instead.

## Why use C++ at all?

Since GMP is very difficult to use without operators, and it has C++ support, using C++ becomes a natural choice. C++ is backwards compatible with C, for the most part, which is very convient. As well, for anything we need that isn't C++ in GMP, with a simple union, we can access the C side of GMP as well.

## Why not use C++ for the entire project?

C grants us more control of the way the code works, and is just as simple as C++ for everything except GMP related code. As well, C++ is backwards compatible with C, meaning that we don't have to convert everything simply because we use a little C++.
