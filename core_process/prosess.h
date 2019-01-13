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


namespace hell_and_haven {
namespace process_core {
#define FINISHED_PID -3




///this class provide a set of arguments for process
///this class consist int argc and const char* argv[]
///which we use int main(int argc, const char* argv[])
class Exe_arg
{
	public:
    Exe_arg(){}

		std::vector<std::string> argv_;
        int argc(){return argv_.size() + 1;}
        Exe_arg(int argc, ...)
        {
            va_list ap;
            va_start(ap,argc);
            for(int i = 0; i< argc; i++)
                argv_.push_back(va_arg(ap,std::string));
            va_end(ap); //without va_end behavior undefined
        }
		char** cstr_argv();
        Exe_arg(int argc, char** argv);

};
/*!
 * \brief The Process class is abstract class of prosesses in UNIX-like systems
 *
 */
class Process
{
public:

virtual ~Process(){}

/// construct object of Process
Process(std::shared_ptr<Process> parent_ptr);
Process(const Process &copy) = delete;

Process(Process && lv_copy) = delete;
void operator = (const Process &copy) = delete;
void operator = (Process && rv_copy) = delete;
/// this functions start process using  using pid_t fork() from C POSIX library
/// and add children`s PID in list
void start_like_fork(const Exe_arg& arg);
void start_like_fork(int argc, char** argv);

//!this is abstract function, that emit, when process strart
virtual int fake_main(const Exe_arg &arg = Exe_arg()) = 0;

/// get any signal that children process is finished
///  and reset his pid in list to FINISHED_PID
//TODO get


protected:
std::list<pid_t> childrens_pids;
private:
std::shared_ptr<Process> _parent_ptr;

};


}
}




