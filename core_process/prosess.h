#pragma once
#include<map>
#include <unistd.h>
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <iterator>
#include <cstdarg>

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
    private:		
	int pid_;
	int group_;
	int user_;
    std::vector<Process> childrens;
    Process* parent;	
};

class ProcessFubric
{
	public:
		static Process rvCreateProcess();
};

//Process main_process;
}



