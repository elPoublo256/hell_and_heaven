#include "psx_pipe.h"
#include <unistd.h>
hh::core_ipc::Base_Pipe::Base_Pipe()
{
     if(pipe(__fd) == -1)
     {
         throw hh::core_ipc::PipeError();
     }
}


#ifdef __USE_GNU
hh::core_ipc::Base_Pipe::Base_Pipe(const int &flag)
{
    if(pipe2(__fd,flag) == -1)
    {
        throw hh::core_ipc::PipeError();
    }

}
#endif


hh::core_ipc::ReadPipe::ReadPipe(const Base_Pipe &piarpipe)
    : BaseReadFile(piarpipe.get_read_fd())
{
 if(close(piarpipe.get_write_fd()) != 0)
 {
     throw hh::core_ipc::PipeError("error close write_fd for reading pipe");
 }
}

hh::core_ipc::WritePipe::WritePipe(const Base_Pipe &piarpipe)
    : BaseWriteFile(piarpipe.get_write_fd())
{
    if(close(piarpipe.get_read_fd()) != 0)
    {
        throw hh::core_ipc::PipeError("error close read_fd for writing pipe");
    }
}

