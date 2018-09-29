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

namespace processes
{
///this class provide a set of arguments for process
///this class consist int argc and const char* argv[]
///which we use int main(int argc, const char* argv[])
class Exe_arg
{
	public:
		std::vector<std::string> argv_;

		auto argc(){return argv_.size() + 1;}
		Exe_arg(int argc, ...);
		char** cstr_argv();


};

class Process
{
	public:
virtual ~Process();
virtual void start(const Exe_arg &arg);
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
	///ilename must be either a binary executable, or a script starting with a line of the form:
	//  #! interpreter [optional-arg] 	
 	virtual void exe_programm(const std::string &file_name, const Exe_arg &args);
	void set_ostream(std::ostream* out_prt) noexcept {out = out_prt;}
	void set_istream(std::istream* in_prt)  noexcept {in  = in_prt;}
	
    private:		
	int pid_;
	int group_;
	int user_;
    std::vector<Process> childrens;
    Process* parent;
    std::ostream* out = &std::cout;
    std::istream* in = &std::cin;
};

class ProcessFubric
{
	public:
		static Process rvCreateProcess();
};

//Process main_process;
}



