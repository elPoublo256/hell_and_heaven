#include "../core_process/pipe_process.h"
#include <iostream>

class MyWritePipe : public hh::WritePipeProcess
{
    int fake_main(const hh::Exe_arg &arg)
    {

        for(int i = 0; i < 100; i ++)
        {
        std::cout << "Write in pipe"<<std::endl;
        *pipe_write << i;
        return 0;
        }
    }
};

class MyReadPipe : public hh::ReadPipeProcess
{

    int fake_main(const hh::Exe_arg &arg)
    {
        for(;;)
        {
        int from_pipe;
        *pipe_read >> from_pipe;
        std::cout<<"get from pipe (" << from_pipe <<")"<<std::endl;
        return 0;
        }
    }
};

int main()
{
    MyWritePipe pw;
    MyReadPipe pr;
    hh::connect(pr, pw);

    pw.start();
    pr.start();

	return 0;
}
