#/bin/bash

cmake .
make
rm CMakeCache.txt cmake_install.cmake Makefile
rm -r CMakeFiles
