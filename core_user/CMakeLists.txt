SET(COMPILE_OPTIONS -Wpedantic -Wall -Wextra -std=c++14 -lcrypt)
add_library(core_user group.h group.cpp user.h user.cpp)

add_library(core_login psx_login.h psx_login.cpp)
target_link_libraries(core_login core_user)
