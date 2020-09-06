#include "psx_pipe.h"
#include <unistd.h>

hh::core_ipc::Base_Pipe::Base_Pipe()
{
    pipe(__pairpipe);
    __read_pipe_ptr = std::make_shared<hh::core_ipc::ReadPipe>(get_read_fd());

    __write_pipe_ptr = std::make_shared<hh::core_ipc::WritePipe>(get_write_fd());
    }

