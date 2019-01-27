#include "pipe_process.h"
#include <unistd.h>
#include <fcntl.h>
#include "../hh_exceptions/hh_exceptions.h"
using namespace hh;


hh::PipeProcessBase::PipeProcessBase(std::shared_ptr<Base_Process> parent) :
    hh::Fork_Process(parent){}

hh::ReadPipeProcess::ReadPipeProcess(std::shared_ptr<Base_Process> parent) :
    hh::PipeProcessBase(parent){}

hh::WritePipeProcess::WritePipeProcess(std::shared_ptr<Base_Process> parent) :
    hh::PipeProcessBase(parent){}

void hh::connect(const ReadPipeProcess &reader, const WritePipeProcess &writer)
{
    int pipe_fd[2];
    if(pipe(pipe_fd) == -1)
        throw hh::ErrnoException();

    reader._pipe_fd = pipe_fd[0];
    reader.no_its_pipe_fd = pipe_fd[1];
    writer._pipe_fd = pipe_fd[1];
    writer.no_its_pipe_fd = pipe_fd[0];

}


void ReadPipeProcess::start(const Exe_arg &arg)
{
    auto pid = fork();
    if(pid != 0 && pid != -1)
    {
        //_parent_ptr->childrens_pids.push_back(pid);
    }

    if(pid == 0)
    {
     close(no_its_pipe_fd);
     pipe_read = std::move(decltype(pipe_read)(new hh::Base_IFile_Stream(_pipe_fd)));
     exit(fake_main(arg));

    }

    if(pid == -1)
    {
        throw hh::ErrnoException();
    }

}

void WritePipeProcess::start(const Exe_arg &arg)
{
    auto pid = fork();
    if(pid != 0 && pid != -1)
    {
     //   _parent_ptr->childrens_pids.push_back(pid);
    }

    if(pid == 0)
    {
     close(no_its_pipe_fd);
     pipe_write = std::move(decltype(pipe_write)(new hh::Base_OFile_Stream(_pipe_fd)));
     exit(fake_main(arg));
    }

    if(pid == -1)
    {
        throw hh::ErrnoException();
    }

}



