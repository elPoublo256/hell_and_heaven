#pragma once
#include<map>
#include <unistd.h>
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <iterator>
#include <string.h>
#include <list>
#include <stdarg.h>
//typedef  typename std::function<int(const &Exe_arg)> MainFType;

namespace processes
{

class Exe_arg;
///this class provide a set of arguments for process
class Exe_arg
{
	public:
		int argc_;
		std::vector<std::string> argv_;
	   
//		Exe_arg(std::string argv...)	{	}
		Exe_arg(int argc, ...)
		{
			va_list ap;
			va_start(ap,argc);
			for(int i = 0; i< argc; i++)
				argv_.push_back(va_arg(ap,std::string));

			va_end(ap); //without va_end behavior undefined
		}

	private:
	//	copy_to_list(std::string arstr)	{	}
	  // 	copy_to_list(std::string arg_str, std::string...Args)	{	}
};

class Process
{
	public:
virtual ~Process();
//virtual void start(int argc, const char* argv[]){start(Exe_arg(argv));}
virtual void start(Exe_arg arg);
//    void stop();
//	void delete_self();
//	void run_file(std::string exe_file_name,const char* argv[]);
//	void fork();
//	private:
//	friend class ProcessFubric;
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
	std::function<int(Exe_arg)>  main = [](Exe_arg arg){return 0;};
};

}



