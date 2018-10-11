cmake_minimum_required(VERSION 2.8.3)

project(hell_and_heaven)

SET(CMAKE_CXX_STANDART 14)

SET(COMPILE_OPTIONS -Wpedantic -Wall -Wextra)

#SET(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(core_process ./core_process/prosess.cpp ./core_process/prosess.h)

add_library(core_files ./core_files/file_stream.cpp ./core_files/file_stream.h)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable( test1 ./tests/test1.cpp)

add_executable( test_process ./tests/test_process.cpp)

add_executable( testpid tests/test_pid_no_change.cpp)

add_executable( test_run tests/test_simple_main.cpp)

target_link_libraries(test1 ${Boost_LIBRARIES})

target_link_libraries(test_process  ${Boost_LIBRARIES} core_process)

target_link_libraries(testpid  ${Boost_LIBRARIES})

target_link_libraries(test_run core_process)

add_executable(test_exe_arg tests/test_exe_arg.cpp)

target_link_libraries(test_exe_arg ${Boost_LIBRARIES} core_process)

add_executable(test_fstream ./core_files/tests/test_filestreams.cpp)

target_link_libraries(test_fstream ${Boost_LIBRARIES} core_files)

add_test(NAME Test_exe_arg COMMAND test_exe_arg)
