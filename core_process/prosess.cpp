#include "prosess.h"
#include "../hh_exceptions/hh_exceptions.h"
#include <iostream>
using namespace hh;

char** Exe_arg::cstr_argv()
{
    int _argc = argc();
    char** res = new char*[_argc];
    for(int i = 0; i < _argc - 1; i++)
    {
        res[i] = new char[argv_[i].length()];
        strcpy(res[i], argv_[i].c_str());
    }
    res[_argc - 1 ] = NULL;
 return res;

}

Exe_arg::Exe_arg(int argc, char **argv)
{
    argv_.reserve(argc);
    for(int i = 0; i < argc - 1; i++)
    {
        argv_.push_back(std::string(argv[i]));
    }
}

Base_Process::Base_Process(const int &in_fd, const int &out_fd) :
    hh_out(out_fd), hh_in(in_fd)
{

}

Fork_Process::Fork_Process(std::shared_ptr<Base_Process> parent_ptr)
{

     _parent_ptr = parent_ptr;

}

void Fork_Process::start(const Exe_arg &arg)
{
        print_log() << __FUNCTION__<<" "<< std::endl;
        int pid = fork();
        switch (pid) {
        case -1:
            throw hh::ErrnoException();
            break;

        case 0:
        {
            _pid = getpid();
            print_log() << "EMIT FAKE MAIN"<< std::endl;
            int resalt = fake_main(arg);
            print_log() << "finish with code "<<resalt<<std::endl;
            exit(resalt);
        }
            break;

        default:

            print_log() << "add as shildren "<<pid << std::endl;
            //_parent_ptr->childrens_pids.push_back(pid);
            break;
        }

}

void Fork_Process::start(int argc, char **argv)
{
    Exe_arg arg(argc, argv);
    start(arg);
}


bool is_Main_Process_Exist = false;

bool MainProcess::is_Main_Exist() { return is_Main_Process_Exist;}
std::shared_ptr<MainProcess> main_ptr;
std::shared_ptr<MainProcess> hh::get_main_ptr()
{
    if(!is_Main_Process_Exist)
    {
        main_ptr = std::move(decltype(main_ptr)(new MainProcess()));
    }
    return main_ptr;}

MainProcess::MainProcess()
{
    if(is_Main_Process_Exist)
    {
        throw std::runtime_error("Main process allready exsist");
    }
    main_ptr = std::shared_ptr<MainProcess>(this);


}



