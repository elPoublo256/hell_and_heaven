set(last_scamke_flags ${CMAKE_CXX_FLAGS})
set(CMAKE_CXX_FLAGS "${last_scamke_flags} -pthread")
add_library(psx_thread psx_thread.h psx_thread.cpp)
set(CMAKE_CXX_FLAGS ${last_scamke_flags})
