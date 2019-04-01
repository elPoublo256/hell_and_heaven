SET(COMPILE_OPTIONS -Wpedantic -Wall -Wextra -std=c++14 -lcrypt)
add_library(core_user group.h group.cpp user.h user.cpp)

