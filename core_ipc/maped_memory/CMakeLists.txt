add_library(psx_mmap psx_mmap.h psx_mmap.cpp)
target_link_libraries(psx_mmap psx_filesystem hh_exception)
