#include "../core_ipc/data_interection/pipes/psx_pipe.h"
#include "../core_process/processes_controller.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>

#define BUF_SIZE 5
hh::core_ipc::Base_Pipe* b_pipe;
class ProcessA : public hh::process::Base_Process
{
public:
    virtual void action() override
    {
        auto write_ptr = b_pipe->get_write();
        for(int i = 0; i < 10; i++)
        {
            write_ptr->psx_write(&i,sizeof(int));
            std::cout<<"pid = "<<getpid()<<" write "<<i<<std::endl;
            sleep(1);

        }
    }
};

class ProcessB : public hh::process::Base_Process
{
    virtual void action() override
    {
        auto read_ptr = b_pipe->get_read();

        for(int i = 0; i < 10; i++)
        {
            int m;
            read_ptr->psx_read(&m, sizeof(int));
            std::cout<<"pid = "<<getpid()<<" read "<<m<<std::endl;
            sleep(1);
        }

    }
};



int main()
{
    b_pipe = new hh::core_ipc::Base_Pipe();
    std::cout<<"read fd = "<<b_pipe->get_read_fd()<<" write fd = "<<b_pipe->get_write_fd()<<std::endl;
    ProcessA a;
    ProcessB b;
    hh::process::Process_Controllers cont;
    cont.run_process(a);
    sleep(1);
    cont.run_process(b);
    cont.whait_process(a,WNOHANG);
    cont.whait_process(b,WNOHANG);





}
