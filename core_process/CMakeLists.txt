
add_library(vir_mem ./vir_mem/vir_mem.h
                    ./vir_mem/vir_mem.cpp)

add_library(core_process prosess.cpp prosess.h
	exe_arg.h
	exe_arg.cpp
	base_process.h 
	base_process.cpp)
target_link_libraries(core_process hh_exception psx_files vir_mem)

#add_library(pipe_process pipe_process.h pipe_process.cpp)
#target_link_libraries(pipe_process core_process)
