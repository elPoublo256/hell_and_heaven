
add_executable(run_example_pipe examle_pipe.cpp)
target_link_libraries(run_example_pipe pipe_process)


add_executable(run_example_fork example_fork.cpp)
target_link_libraries(run_example_fork core_process)
