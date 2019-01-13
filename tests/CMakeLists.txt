find_package(Boost COMPONENTS unit_test_framework REQUIRED)



add_executable( test_process test_process.cpp)

add_executable( test_filestreams test_filestreams.cpp)

add_executable( test_exearg test_exearg.cpp)

target_link_libraries(test_process  ${Boost_LIBRARIES} core_process)

target_link_libraries(test_filestreams  ${Boost_LIBRARIES} core_filestream)

target_link_libraries(test_exearg  ${Boost_LIBRARIES} core_filestream)


add_test(Test_process COMMAND test_process)

add_test(Test_filestreams COMMAND test_filestreams)

add_test(Test_exe_arg COMMAND test_exearg)
