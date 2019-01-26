#include "pipe_process.h"
#include <unistd.h>
#include <fcntl.h>
#include "../hh_exceptions/hh_exceptions.h"
using namespace hh;


void hh::connect(const ReadPipeProcess &reader, const WritePipeProcess &writer)
{

}

ReadPipeProcess::ReadPipeProcess(std::shared_ptr<Base_Process> parent)
    : Fork_Process(parent){}




void hh::ReadPipeProcess::start(const Exe_arg &arg)
{


}


ReadPipeProcess::~ReadPipeProcess()
{
    if(_pipe_fd != -1){
        close(_pipe_fd);
    }
}
