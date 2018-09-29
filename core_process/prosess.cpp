#include "prosess.h"
#include  <utility>
using namespace processes;


Process::Process()
{
	pid_ = getpid();
	user_ = getuid();
	group_ = getgid();
}

Process::~Process()
{
}



void Process::start(Exe_arg arg)
{
	auto res = main(arg);
	std::cout << "process return code " << res;
}
/*void Process::run_file(std::string exe_file_name, const char* argv[])
{
  //if(execvp(exe_file_name.c_str(), argv) == -1)
  {
	  //print error
  }
}
	*/
