cmake_minimum_required(VERSION 3.1)

project(hell_and_heaven)

SET(CMAKE_CXX_STANDART 14)

#SET(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(core_process ./core_process/prosess.cpp ./core_process/prosess.h)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable( test1 ./tests/test1.cpp)

add_executable( test_process ./tests/test_process.cpp)

add_executable( testpid tests/test_pid_no_change.cpp)

target_link_libraries(test1 ${Boost_LIBRARIES})

target_link_libraries(test_process  ${Boost_LIBRARIES} core_process)

target_link_libraries(testpid  ${Boost_LIBRARIES})

add_test(NAME Test1 COMMAND test1)

add_test(NAME Testpid COMMAND testpid)


