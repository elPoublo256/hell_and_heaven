cmake_minimum_required(VERSION 2.8.3)
project(hell_and_heaven)

SET(CMAKE_CXX_STANDART 14)
SET(CMAKE_CXX_FLAGS "-std=c++14 -g")
SET(COMPILE_OPTIONS -Wpedantic -Wall -Wextra -std=c++14 -ftext-numeric-literals)


enable_testing()

include(CTest)

add_subdirectory(hh_exceptions)

add_subdirectory(core_files)

add_subdirectory(core_process)

add_subdirectory(core_user)

add_subdirectory(core_info)

add_subdirectory(core_thread)

add_subdirectory(core_syslog)

add_subdirectory(tests)

add_subdirectory(examples)

add_subdirectory(experiments)

add_subdirectory(core_ipc)
