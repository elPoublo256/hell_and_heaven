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
#include <memory>
#include <signal.h>
#include <unordered_map>
#include "../core_files/file_stream.h"
#include <list>
#include <iostream>
//TODO make check create dump file
//#ifdef WCOREDUMP
//#define IS_CREATE_FILE_DUMP WCOREDUMP
//#elif

namespace hh {

#define FINISHED_PID -3




///this class provide a set of arguments for process
///this class consist int argc and const char* argv[]
///which we use int main(int argc, const char* argv[])
class Exe_arg
{
	public:
    Exe_arg(){}

		std::vector<std::string> argv_;
        int argc(){return argv_.size() + 1;}
        Exe_arg(int argc, ...)
        {
            va_list ap;
            va_start(ap,argc);
            for(int i = 0; i< argc; i++)
                argv_.push_back(va_arg(ap,std::string));
            va_end(ap); //without va_end behavior undefined
        }
		char** cstr_argv();
        Exe_arg(int argc, char** argv);

};
/*!
 * \brief The Process class is abstract class of prosesses in UNIX-like systems
 *this is abstract class
 */
class Base_Process
{
public:
    Base_Process(const int& in_fd = STDIN_FILENO,const int& out_fd = STDOUT_FILENO);
    virtual void start(const Exe_arg& arg) = 0;
    virtual void start(int argc, char** argv) {this->start(Exe_arg(argc, argv));}
    inline decltype(std::cout)& print_log() {return std::cout << "PID "<<getpid()<<" ";}
    //!this is abstract function, that emit, when process strart
    virtual int fake_main(const Exe_arg &arg = Exe_arg()) = 0;
std::list<pid_t> childrens_pids;

protected:
Base_IFile_Stream hh_in;
Base_OFile_Stream hh_out;
pid_t _pid;

};


//!
//! \brief The MainProcess class
//!this is abstract class of first process in full tree processes in program
//! You can initialize only one object of realization of this class
//! else Constructor of second object throw std::runtime_error

class MainProcess : public Base_Process
{
public:
static bool is_Main_Exist();
protected:

    MainProcess();
    friend std::shared_ptr<MainProcess> get_main_ptr();
    void start(const Exe_arg &arg) override final {this->fake_main(arg);}
    int fake_main(const Exe_arg &arg) override{}


};

 std::shared_ptr<MainProcess> get_main_ptr();



class Fork_Process : public Base_Process
{
public:

virtual ~Fork_Process(){}

/// construct object of Process
Fork_Process(std::shared_ptr<Base_Process> parent_ptr = get_main_ptr());
Fork_Process(const Fork_Process &copy) = delete;

Fork_Process(Fork_Process && lv_copy) = delete;
void operator = (const Fork_Process &copy) = delete;
void operator = (Fork_Process && rv_copy) = delete;
/// this functions start process using  using pid_t fork() from C POSIX library
/// and add children`s PID in list
void start(const Exe_arg& arg = Exe_arg()) override;
void start(int argc, char** argv) override ;

/// get any signal that children process is finished
///  and reset his pid in list to FINISHED_PID
//TODO get
protected:
std::shared_ptr<Base_Process> _parent_ptr;

};


//!
//! \brief The Exe_Process class
//!this calss start process using execl


}





