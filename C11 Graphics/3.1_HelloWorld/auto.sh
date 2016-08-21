#! /bin/sh
make clean
make -f Makefile_lib clean
make -f Makefile_lib
make
exit
