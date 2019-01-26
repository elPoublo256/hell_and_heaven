#include "../core_process/pipe_process.h"
#include <iostream>

class MyWritePipe : public hh::WritePipeProcess
{
    int fake_main(const hh::Exe_arg &arg)
    {
        std::cout << "Write in pipe"<<std::endl;
        *pipe_write << 1;
    }
};

class MyReadPipe : public hh::ReadPipeProcess
{

    int fake_main(const hh::Exe_arg &arg)
    {
        int from_pipe;
        *pipe_read >> from_pipe;
        std::cout<<"get from pipe (" << from_pipe <<")"<<std::endl;
    }
};

int main()
{
    MyWritePipe pw;
    MyReadPipe pr;
	return 0;
}
