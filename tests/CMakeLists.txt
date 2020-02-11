find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_psx_file test_psx_file.cpp)
target_link_libraries(test_psx_file psx_files ${Boost_LIBRARIES} )

#add_executable(run_test_psx_streambuf test_psx_streambud.cpp)
#target_link_libraries(run_test_psx_streambuf ${Boost_LIBRARIES} core_filestream)

#add_executable( run_test_filestreams test_filestreams.cpp)
#target_link_libraries(run_test_filestreams  ${Boost_LIBRARIES} core_filestream)

add_executable( run_test_exearg test_exearg.cpp)
target_link_libraries(run_test_exearg  ${Boost_LIBRARIES} core_process)

add_executable( run_test_base_process test_base_process.cpp)
target_link_libraries(run_test_base_process ${Boost_LIBRARIES} core_process)

#add_executable( run_test_pipe_process test_pipe_process.cpp)

#target_link_libraries(run_test_process  ${Boost_LIBRARIES} core_process)

add_executable(test_setsignals test_setsignals.cpp)
target_link_libraries(test_setsignals psx_signals ${Boost_LIBRARIES})


add_executable(test_signal_handler test_signal_handler.cpp)
target_link_libraries(test_signal_handler psx_signals ${Boost_LIBRARIES})

add_test(Test_signal_Handler test_signal_handler)

add_test(Test_filestreams run_test_filestreams)

add_test(Test_exe_arg run_test_exearg)

add_test(Test_PSX_File test_psx_file)
