#/bin/bash
#cd ../
#mkdir build_hell_anf_heaven
#cd build_hell_anf_heaven
#cmake hell_and_heaven
cmake .
make
rm CMakeCache.txt cmake_install.cmake Makefile
rm -r CMakeFiles
