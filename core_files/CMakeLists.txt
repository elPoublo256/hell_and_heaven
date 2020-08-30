
find_package (Threads)

add_library(psx_files psx_files.h psx_files.cpp)
target_link_libraries(psx_files hh_exception psx_base_file psx_base_bufer)

#add_library(psx_directory psx_directory.h psx_directory.cpp)
#target_link_libraries(psx_directory psx_files hh_exception)

#add_library(psx_filesystem filesystem.h filesystem.cpp)
#target_link_libraries(psx_filesystem psx_directory psx_files hh_exception core_user)

#add_library(psx_notify notify.h notify.cpp)
#target_link_libraries(psx_notify psx_directory ${CMAKE_THREAD_LIBS_INIT})
#add_library(core_filestream file_stream.cpp file_stream.h psx_streambuf.h
#        psx_streambuf.cpp psx_read_streambuf.h psx_write_streambuf.h)


#target_link_libraries(core_filestream psx_files)
