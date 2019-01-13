#include "prosess.h"
using namespace hell_and_haven::process_core;

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


Process::Process(std::shared_ptr<Process> parent_ptr)
{

     _parent_ptr = parent_ptr;

}

void Process::start_like_fork(const Exe_arg &arg)
{
        auto pid = fork();
        if(pid != 0 && pid != -1)
        {
            _parent_ptr->childrens_pids.push_back(pid);
        }
        if(pid == 0)
        {
         this->fake_main(arg);
        }

}

void Process::start_like_fork(int argc, char **argv)
{
    Exe_arg arg(argc, argv);
    start_like_fork(arg);
}




