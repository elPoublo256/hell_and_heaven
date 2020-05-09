#pragma once
#include "base_process.h"
#include <map>
#include <string>
#include <sys/wait.h>
#include "../hh_exceptions/hh_exceptions.h"
#include "../core_files/psx_files.h"

namespace hh {
namespace process {

/*!
 * \brief The Process_Controllers class provide monipulation with process
 *
 */
struct WaitStatus
{
    static bool is_normal_exit(const int& s) noexcept  {return WIFEXITED(s);}
    static bool is_signal_exit(const int& s) noexcept {return WIFSIGNALED(s);}
    static bool is_stop_signal(const int& s) noexcept {return WIFSTOPPED(s);}
    static bool is_continue(const int& s) noexcept {return WIFCONTINUED(s);}

     bool is_normal_exit() noexcept {return WIFEXITED(c_status);}
     bool is_signal_exit() noexcept {return WIFSIGNALED(c_status);}
     bool is_stop_signal() noexcept {return WIFSTOPPED(c_status);}
     bool is_continue() noexcept {return WIFCONTINUED(c_status);}
     WaitStatus(){}
     WaitStatus(const int& glibc_status) {c_status = glibc_status;}
    int c_status;
    pid_t pid;
};

class Process_Controllers_Error : public hh::ErrnoException
{
public:
    std::string __err;
   Process_Controllers_Error(const std::string& err) : hh::ErrnoException(),
       __err(err + std::string(":") + ErrnoException::what())
   {

   }
   std::string what(){return __err;}
};


class ErrorWait : public Process_Controllers_Error
{
public:
    ErrorWait() : Process_Controllers_Error(std::string("Error waiting")){}
};

class Process_Controllers
{
public:


    /*!
     * \brief hh_fork - run process using glibc function fork after preparing
     * (emit prepare_before_start() then fork then if pid == 0 action())
     * and save pointer of object of process-class in map of childrens-processes
     * and set pid in this object of process-class
     * \param process - object of process-class
     */
    Process_Controllers(){}
    virtual ~Process_Controllers(){}
    virtual void run_process(hh::process::Base_Process& process);
    //static void fork(const hh::process::Base_Process& process);

    /*!
     * \brief whait_process
     * block curent thread while a process with pid seted in process-object
     * working ore stoped by signal using waitpid()
     * \param process - process-object with seted pid
     * \param options_whait - option of waiting like parameter for waitpid/wait
     * \return return WaitStatus as status whaiting
     */
    WaitStatus whait_process(const Base_Process& process, const int& options_whait);

    /*!
     * \brief whait_process
     * block curent thread while a process with pid
     * working ore stoped by signal using waitpid()
     * \param pid - PID of waited process
     * \param options_whait option of waiting like parameter for waitpid/wait
     * \return WaitStatus as status whaiting with pid as result of whaitpid()
     */
    WaitStatus whait_process(const pid_t& pid,  const int& options_whait);
    /*!
     * \brief whait_children - wait any children-process using wait from glibc
     * \return WaitStatus as status whaiting with pid as result of whaitpid()
     */

    /*!
     * \brief whait_children block curent thread while any childreon process will not exited
     * using glibc function whait
     * \return WaitStatus as status whaiting with pid as result of whait()
     */
    WaitStatus whait_children();

    /*!
     * \brief c_strigs_environ_from_map
     * convert map to array of C-strings in format <Key=Value>
     * last pointer to string is NULL
     * WARNING!!! DO NOT FORGET free result this function after using if you dont want get leek memory
     * \param e_map
     * \return C-strings in format <Key=Value> last pointer to string is NULL
     */
    static char** c_strigs_environ_from_map(const std::map<std::string, std::string>& e_map);


    /*!
     * \brief run_program_in_this_process
     * run program in this process using execve()
     * \param file_name - exucatable file
     * \param arg - arguments of main function in hh-stile Do not forgot add name file here as first arg
     * \param environ - new envirements of process seted in map<Key,Value>
     */
    void run_program_in_this_process(const std::string& file_name,
                                     const Exe_arg& arg,
                                     const std::map<std::string, std::string> environ);
    /*!
     * \brief run_program_in_this_process
     * run program in this process using execve()
     * \param file_name
     * \param arg - arguments of main function in hh-stile. Do not forgot add name file here as first arg
     */
    void run_program_in_this_process(const std::string& file_name,
                                     const Exe_arg& arg);

    /*!
     * \brief run_program_in_this_process
     * run program in this process using fexecve()
     * \param file - object of file with filediscriptor
     * \param arg - arguments of main function in hh-stile. Do not forgot add name file here as first arg
     * \param environ - - new envirements of process seted in map<Key,Value>
     */
    void run_program_in_this_process(const hh::psx_file::BasePSXFile& file,
                                     const Exe_arg& arg,
                                     const std::map<std::string, std::string> &environ);

    //TODO make set methods run processes using vfork()

    //TODO make set methods run processes using clone()





};


}
}
