#include "../core_ipc/data_interection/pipes/psx_pipe.h"
#include "../core_process/processes_controller.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>

#define BUF_SIZE 5
hh::core_ipc::Base_Pipe b_pipe;
class ProcessA : public hh::process::Base_Process
{
public:
    virtual void action() override
    {
        hh::core_ipc::ReadPipe r_pipe(b_pipe);
        char c;
        for(int i = 0; i < BUF_SIZE +1; i++)
        {
            r_pipe.psx_read(&c,1);
            std::cout << "pid A = "<<getpid()<<" get c="<<c<<std::endl;
        }

    }
};

class ProcessB : public hh::process::Base_Process
{
    virtual void action() override
    {
        std::cout << "pid B ="<<getpid()<<" writer"<<std::endl;
        char arr[BUF_SIZE];
        for(int i = 0; i < BUF_SIZE; i++)
        {
            arr[i] = 'a' + i;
            std::cout << "pid B = "<<getpid()<<":arr["<<i<<"]="<<arr[i]<<std::endl;
        }
        hh::core_ipc::WritePipe w_pipe(b_pipe);
        w_pipe.psx_write((char*)arr,5);
        std::cout << "end write pipe"<<std::endl;
    }
};



int main()
{
    ProcessA a;
    ProcessB b;
    hh::process::Process_Controllers cont;
    cont.run_process(a);
    cont.run_process(b);
    cont.whait_process(a,WNOHANG);
    cont.whait_process(b,WNOHANG);





}
