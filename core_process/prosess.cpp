#include "prosess.h"
#include  <utility>





char** Exe_arg::cstr_argv()
{
	int _argc = argc(); 
	char** res = new char*[_argc];
    for(int i = 0; i < _argc; i++)
	{
		res[i] = new char[argv_[i].length()];
        strcpy(res[i], argv_[i].c_str());
	}
	res[_argc - 1 ] = NULL;
 return res;

}

Process::Process()
{
	pid_ = getpid();
	user_ = getuid();
	group_ = getgid();
}

Process::~Process()
{
}



void Process::start(const Exe_arg &arg)
{
    auto pid = fork();
    if(pid > 0)
    {

    }
    else
    {
	auto res = main(arg);
    }
}

void Process:: exe_programm(const std::string &file_name, const Exe_arg &args)
{
}

/*void Process::run_file(std::string exe_file_name, const char* argv[])
{
  //if(execvp(exe_file_name.c_str(), argv) == -1)
  {
	  //print error
  }
}
	*/
