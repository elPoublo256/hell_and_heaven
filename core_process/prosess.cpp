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

char** Exe_arg::cstr_argv()
{
	int _argc = argc(); 
	char** res = new char*[_argc];
	for(int i = 0; i < _argc - 1; i++)
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
	auto res = main(arg);
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
