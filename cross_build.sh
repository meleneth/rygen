#!/bin/sh

export PATH=/var/opt/mxe/usr/bin:$PATH

autoreconf -i
./configure --host=i686-w64-mingw32.static
make clean
make

