
add_library(psx_files psx_files.h psx_files.cpp)
target_link_libraries(psx_files hh_exception)
add_library(core_filestream file_stream.cpp file_stream.h psx_streambuf.h
        psx_streambuf.cpp psx_read_streambuf.h psx_write_streambuf.h)
target_link_libraries(core_filestream psx_files)
