
add_library(psx_files psx_files.h psx_files.cpp)
add_library(core_filestream file_stream.cpp file_stream.h)
target_link_libraries(core_filestream psx_files)
