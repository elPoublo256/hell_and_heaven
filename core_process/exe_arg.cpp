#include "exe_arg.h"
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




