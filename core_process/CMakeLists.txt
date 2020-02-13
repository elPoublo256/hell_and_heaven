
add_library(psx_signals
    psx_signals.h psx_signals.cpp
    psx_signalhandler.h psx_signalhandler.cpp
    static_hanler.h
    psx_alterstack.h psx_alterstack.cpp
    #psx_setsignals.h  psx_setsignals.cpp
    psx2_signal_info.h psx2_signal_info.cpp
    )
target_link_libraries(psx_signals hh_exception)

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
