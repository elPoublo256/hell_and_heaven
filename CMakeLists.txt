cmake_minimum_required(VERSION 2.8.3)

project(hell_and_heaven)

SET(CMAKE_CXX_STANDART 14)

SET(COMPILE_OPTIONS -Wpedantic -Wall -Wextra)

enable_testing()

add_subdirectory(core_process)

add_subdirectory(core_files)

add_subdirectory(tests)


