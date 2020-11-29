#include "processes_controller.h"
#include <string.h>
using namespace hh::process;

void Process_Controllers::run_process(Base_Process &process)
{
    process.prepare_before_start();
    auto new_pid = fork();
    if(new_pid == 0)
    {
        process.prepare_before_start();
        process.action();
        exit(0);
    }
    else if(new_pid > 0)
    {
        process.id.pocess_id = new_pid;
    }
    else if(new_pid < 0)
    {
        throw Process_Controllers_Error("error run process");
    }
}

WaitStatus Process_Controllers::whait_process(const Base_Process &process, const int &options_whait)
{
    WaitStatus res;
    auto err = waitpid(process.id.pocess_id, &res.c_status, options_whait);
    if(err == -1)
    {
       throw ErrorWait();
    }
    //TODO if(err == 0)
    res.pid = err;
    return res;
}

WaitStatus Process_Controllers::whait_process(const pid_t &pid, const int &options_whait = WNOHANG)
{
    WaitStatus res;
    auto pidd = pid;
    auto err = waitpid(pidd, &res.c_status, options_whait);
    if(err == -1)
    {
       throw ErrorWait();
    }
    res.pid = err;
    //TODO if(err == 0)
    return res;
}

WaitStatus Process_Controllers::whait_children()
{
    WaitStatus res;
    auto err = wait(&res.c_status);
    if(err == -1)
    {
       throw ErrorWait();
    }
    res.pid = err;
    //TODO if(err == 0)
    return res;
}

char** Process_Controllers::c_strigs_environ_from_map(const std::map<std::string, std::string> &e_map)
{
    auto size = e_map.size();
    char** res = (char**)malloc((size + 1) * sizeof(char*));
    auto it = e_map.begin();
    for(int i = 0; i < size; i++)
    {
        std::string key = (*it).first;
        std::string val = (*it).second;
        auto s_size = key.size() + val.size() + 1;
        res[i] = (char*)malloc(s_size * sizeof(char));
        auto kv = key + std::string("=") + val;
        memcpy(res[i],kv.data(), s_size * sizeof(char));

    }
    res[size] = NULL;

    return res;
}

void Process_Controllers::run_program_in_this_process(const std::string &file_name,
                                                      const Exe_arg &arg,
                                                      const std::map<std::string, std::string> environ)
{
    auto size_env = environ.size();
    auto env_cstr = Process_Controllers::c_strigs_environ_from_map(environ);
    auto arg_cstr = arg.cstr_argv();
    //WHE DONT NEED FREE ARRAYS if whe run new programm
    auto err = execve(file_name.c_str(),arg_cstr, env_cstr);
    if(err == -1)
    {
        for(int i =0; i < environ.size();i++)
        {
            free(env_cstr[i]);
        }
        free(env_cstr);
        throw Process_Controllers_Error(std::string("ERROR execve"));
    }
}

void Process_Controllers::run_program_in_this_process(const std::string &file_name,
                                                      const Exe_arg &arg)
{
    auto arg_cstr = arg.cstr_argv();
    auto err = execv(file_name.c_str(),arg_cstr);
    if(err == -1)
    {
        throw Process_Controllers_Error(std::string("ERROR execv"));
    }

}

/*
void Process_Controllers::run_program_in_this_process(const hh::core_files::Base_FS_File &file,
                                                      const Exe_arg &arg,
                                                      const std::map<std::string, std::string>& environ)
{
    auto arg_cstr = arg.cstr_argv();
    auto env_cstr = Process_Controllers::c_strigs_environ_from_map(environ);
    auto err = fexecve(file.get_file_discriptror(), arg_cstr, env_cstr);
    if(err == -1)
    {
        for(int i =0; i < environ.size();i++)
        {
            free(env_cstr[i]);
        }
        free(env_cstr);
        throw Process_Controllers_Error(std::string("ERROR fexecve"));
    }
}
*/
