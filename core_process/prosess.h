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
#include "../core_files/file_stream.h"

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


};

class Process
{
	public:
virtual ~Process();
virtual void start(const Exe_arg &arg);
Process(const Process &copy) = delete;
Process(Process && rv_copy) = delete;
void operator = (const Process &copy) = delete;
void operator = (Process && rv_copy) = delete; 
//    void stop();
//	void delete_self();
//	void run_file(std::string exe_file_name,const char* argv[]);
//	void fork();
//	private:
//	friend class ProcessFubric;

std::function<int(const Exe_arg&)> main = [](const Exe_arg& arg){return 0;};

    int get_pid()   noexcept    {return pid_;}
	int get_group() noexcept    {return group_;}
	int get_user()  noexcept    {return user_;}

		Process();
	///load binar programm in memory,replace curent proccess image
	///and run this program with arguments seted in Exe_arg args
 	virtual void exe_programm(const std::string &file_name, const Exe_arg &args);
//     auto get_ostream() {return *out_prt << "";}
//     auto get_istrem() {return *in_prt << "";}
//   	auto git_logstream() {return *log << start_log_str();}
	
    private:		
	int pid_;
	int group_;
    int user_;

};

class ProcessFubric
{
	public:
		static Process rvCreateProcess();
};





