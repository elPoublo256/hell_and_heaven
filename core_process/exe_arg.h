#pragma once
#include<map>
#include <unistd.h>
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <iterator>
#include <cstdarg>
#include <string.h>
#include <memory>
#include <signal.h>
#include <unordered_map>
#include "../core_files/file_stream.h"
#include <list>
#include <iostream>
//TODO make check create dump file
//#ifdef WCOREDUMP
//#define IS_CREATE_FILE_DUMP WCOREDUMP
//#elif

namespace hh {

#define FINISHED_PID -3




///this class provide a set of arguments for process
///this class consist int argc and const char* argv[]
///which we use int main(int argc, const char* argv[])
class Exe_arg
{
	public:
    Exe_arg(){}

		std::vector<std::string> argv_;
        int argc() const {return argv_.size() + 1;}
        Exe_arg(int argc, ...)
        {
            va_list ap;
            va_start(ap,argc);
            for(int i = 0; i< argc; i++)
                argv_.push_back(va_arg(ap,std::string));
            va_end(ap); //without va_end behavior undefined
        }
        char** cstr_argv() const;
        Exe_arg(int argc, char** argv);


};


}





