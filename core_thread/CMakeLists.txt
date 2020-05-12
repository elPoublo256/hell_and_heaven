

set(last_scamke_flags ${CMAKE_CXX_FLAGS})
set(CMAKE_CXX_FLAGS "${last_scamke_flags} -pthread")
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_library(psx_thread psx_thread.h psx_thread.cpp)
target_link_libraries(psx_thread hh_exception Threads::Threads)
set(CMAKE_CXX_FLAGS ${last_scamke_flags})
