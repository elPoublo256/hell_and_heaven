#include "../core_process/pipe_process.h"
#include <iostream>

class MyWritePipe : public hh::WritePipeProcess
{
    int fake_main(const hh::Exe_arg &arg)
    {

        for(int i = 0; i < 5; i ++)
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
        for(int i = 0; i < 5; i ++)
        {
        int from_pipe;
        *pipe_read >> from_pipe;
        std::cout<<"get from pipe (" << from_pipe <<")"<<std::endl;
        }
        return 0;
    }
};

void example_c_pipe()
{
    int pipefds[2];
    auto res = pipe(pipefds);
    if(res == -1)
    {
        std::cout<< "ERROR PIPE ERRNO="<<errno;
        _exit(1);
    }
     int fd_r = pipefds[0];
     int fd_w = pipefds[1];
     auto pd = fork();
     if(pd == 0)
     {
         close(fd_r);
         for(int i = 0; i < 10; i++)
         {
             auto c = 10 + i;
             write(fd_w, &c, sizeof(int));
         }
         //_exit(0);
     }
     pd = fork();
         if(pd == 0)
         {
             close(fd_w);
             for(int i = 0; i < 10; i++)
             {
                 int c;
                 read(fd_w, &c, sizeof(int));
                 std::cout << "GET "<<c<<" FROM PIPE"<<std::endl;
             }
             //_exit(0);
         }

}

int main()
{
  example_c_pipe();
  //MyWritePipe pw; MyReadPipe pr; hh::connect(pr, pw);
  //pw.start(); pr.start();
	return 0;
}
