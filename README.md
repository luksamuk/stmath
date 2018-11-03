# stmath
First version of math/geometry library for Studium Engine

## Purpose
There is none. This is the first version of libstudium's math library, along
with a macros header, which I created for implementing vector and matrix
operations. This was before I knew a C port of GLM existed (CGLM).

Also included are the test cases for this library, which I have written using
libcheck.

### Does libstudium not use stmath anymore?
It actually still does. Turns out CGLM seems to prioritize 3D stuff. At the time
of this writing, there are no implementations for things like 2D vectors in it,
yet. Since I'm still comfortable with the tool I've built, I prefer to keep using
it, until a tool with better performance comes into play.

## License
Like libstudium, this old portion of it is distributed under the LGPL v3.0
license.

