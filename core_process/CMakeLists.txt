

add_library(core_process prosess.cpp prosess.h)
target_link_libraries(core_process hh_exception psx_files)

#add_library(pipe_process pipe_process.h pipe_process.cpp)
#target_link_libraries(pipe_process core_process)
