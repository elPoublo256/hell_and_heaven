#include "prosess.h"
#include  <utility>
using namespace processes;
Process::Process()
{
}

Process::~Process()
{
}


 Process ProcessFubric::rvCreateProcess()
{
    Process p;
	return std::move(Process());
}

/*void Process::run_file(std::string exe_file_name, const char* argv[])
{
  //if(execvp(exe_file_name.c_str(), argv) == -1)
  {
	  //print error
  }
}
*/
