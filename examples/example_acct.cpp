#include "../core_process/accouting_process.h"
#include "../core_process/base_process.h"
#include "../core_process/processes_controller.h"
#include <thread>
#include <chrono>
#include <iostream>
class TestProcess1 : public hh::process::Base_Process
{
public:
    TestProcess1() : hh::process::Base_Process() {}
    ~TestProcess1(){}
    void action()
    {
        for(int i = 0; i < 5; i++)
        {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout<<"GETPID:"<<getpid() << " LOADEDPID" << this->id.pocess_id<<std::endl;


        }
    }
};


void hh_example()
{
    hh::process::Process_Controllers conntrroller;
    TestProcess1 t1;
    //hh::process::AccoutingInfoFile acf("./acct.dat");
    //acf.set_as_accFile();
    std::cout << "start process1" << std::endl;
    conntrroller.run_process(t1);
    std::cout << "process1 pid = "<<t1.get_Process_ID() << std::endl;
    auto s1 = conntrroller.whait_process(t1, 0);

}

void c_example()
{
    pid_t pid1, pid2;
    printf("start process 1");
    pid1 = fork();
    if(pid1 == 0)
    {
        for(int i = 0; i< 5; i++)
        {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout<<"GETPID:"<<getpid()<<std::endl;

        }
        exit(0);
    }
    else if(pid1 > 0)
    {
        printf("start process1 pid = %d", pid1);
        int statuswait;
        waitpid(pid1,&statuswait,0);
        exit(0);
    }



}



int main()
{

    //c_example();
    hh_example();
    return 0;
}
