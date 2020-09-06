
add_library(psx_base_bufer psx_base_buffer.h psx_base_buffer.cpp)
add_library(psx_base_file psx_base_file.h psx_base_file.cpp)
target_link_libraries(psx_base_file hh_exception)
