cmake_minimum_required(VERSION 3.1)

project(test1)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test1 test1.cpp)

target_link_libraries(test1 ${Boost_LIBRARIES})

add_test(NAME Test1 COMMAND test1)
