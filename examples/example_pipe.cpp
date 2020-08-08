#include "../core_ipc/data_interection/pipes/psx_pipe.h"
#include "../core_process/processes_controller.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>

#define BUF_SIZE 5

int main()
{
    hh::core_ipc::Base_Pipe b_pipe;
    auto pid = fork();
    if(pid == 0)
    {
        hh::core_ipc::ReadPipe r_pipe(b_pipe);
        char c;
        for(int i = 0; i < BUF_SIZE +1; i++)
        {
            r_pipe.psx_read(&c,1);
            std::cout << "pid = "<<getpid()<<" get c="<<c<<std::endl;
        }

    }
    else if(pid > 0)
    {
        std::cout << "pid="<<getpid()<<" writer"<<std::endl;
        char arr[BUF_SIZE];
        for(int i = 0; i < BUF_SIZE; i++)
        {
            arr[i] = 'a' + i;
            std::cout << "pid = "<<getpid()<<":arr["<<i<<"]="<<arr[i]<<std::endl;
        }
        hh::core_ipc::WritePipe w_pipe(b_pipe);
        w_pipe.psx_write((char*)arr,5);
        std::cout << "end write pipe"<<std::endl;

       hh::process::Process_Controllers cont;
       cont.whait_children();
    }

}
