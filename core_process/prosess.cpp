#include "prosess.h"
#include  <utility>
using namespace processes;

Exe_arg::Exe_arg(int argc, ...)                                                                
   {                                                                                         
       va_list ap;                                                                           
       va_start(ap,argc);                                                                    
       for(int i = 0; i< argc; i++)                                                          
           argv_.push_back(va_arg(ap,std::string));                                          
                                                                                             
       va_end(ap); //without va_end behavior undefined                                       
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
	auto res = main(arg);
}
/*void Process::run_file(std::string exe_file_name, const char* argv[])
{
  //if(execvp(exe_file_name.c_str(), argv) == -1)
  {
	  //print error
  }
}
	*/
