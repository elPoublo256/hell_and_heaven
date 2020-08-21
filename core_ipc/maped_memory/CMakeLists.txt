add_library(psx_mmap psx_mmap.h psx_mmap.cpp)
target_link_libraries(psx_mmap psx_filesystem hh_exception)

add_library(possix_mmap possix_shared_memory.h possix_shared_memory.cpp)
target_link_libraries(possix_mmap psx_mmap)
