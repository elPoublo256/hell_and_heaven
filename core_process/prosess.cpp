#include "prosess.h"
#include  <utility>
using namespace processes;

auto foo()
{
	return 0;
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


 Process ProcessFubric::rvCreateProcess()
{
    Process p;
	return p;
}

/*void Process::run_file(std::string exe_file_name, const char* argv[])
{
  //if(execvp(exe_file_name.c_str(), argv) == -1)
  {
	  //print error
  }
}
*/
