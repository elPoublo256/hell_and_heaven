#include "psx_pipe.h"
#include <unistd.h>

hh::core_ipc::ReadPipe::ReadPipe(const Base_Pipe &piarpipe)
    : hh::BaseFD<int>(piarpipe.get_read_fd())
{
 if(close(piarpipe.get_write_fd()) != 0)
 {
     throw hh::core_ipc::PipeError("error close write_fd for reading pipe");
 }
}

hh::core_ipc::WritePipe::WritePipe(const int& fd_write)
    :  hh::BaseFD<int>(fd_write)
{

}

int hh::core_ipc::ReadPipe::psx_read(void *dest, const std::size_t &len)
{
    return read(get_file_discriptror(),dest,len);
}

int hh::core_ipc::WritePipe::psx_write(const void *src, const std::size_t &len)
{
    return write(get_file_discriptror(),src,len);
}

hh::core_ipc::Base_Pipe::Base_Pipe()
{
     if(pipe(__pairpipe) == -1)
     {
         throw hh::core_ipc::PipeError();
     }
}


//#ifdef __USE_GNU
//hh::core_ipc::Base_Pipe::Base_Pipe(const int &flag)
//{
//    if(pipe2(__pairpipe,flag) == -1)
//    {
//        throw hh::core_ipc::PipeError();
//    }

//}
//#endif

//hh::core_ipc::
