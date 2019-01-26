find_package(Boost COMPONENTS unit_test_framework REQUIRED)



add_executable( run_test_process test_process.cpp)

add_executable( run_test_filestreams test_filestreams.cpp)

add_executable( run_test_exearg test_exearg.cpp)

#add_executable( run_test_pipe_process test_pipe_process.cpp)

target_link_libraries(run_test_process  ${Boost_LIBRARIES} core_process)

target_link_libraries(run_test_filestreams  ${Boost_LIBRARIES} core_filestream)

target_link_libraries(run_test_exearg  ${Boost_LIBRARIES} core_filestream)

#target_link_libraries(run_test_pipe_process pipe_process core_process)

add_test(Test_process run_test_process)

add_test(Test_filestreams run_test_filestreams)

add_test(Test_exe_arg run_test_exearg)
