#/bin/bash

cmake .
make
rm CMakeCache.txt cmake_install.cmake Makefile
rm -r CMakeFiles
#for file in ./*;
#do
#	if [[ $file == "CMakeLists.txt" ]];
#	then
#     	echo " there $file"
#	fi
#done
