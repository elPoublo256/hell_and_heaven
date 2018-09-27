#pragma once
#include<map>
#include <unistd.h>
#include <vector>
#include <string>
//#include <functional>
//typedef std::function<int(int, char*)> MainFType;

namespace processes
{
class Process
{
	public:
	~Process();
   
//	void strart(std::is_function<void()> f);
//    void stop();
//	void delete_self();
//	void run_file(std::string exe_file_name,const char* argv[]);
//	void fork();
//	private:
//	friend class ProcessFubric;
//    MainFType main;
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



