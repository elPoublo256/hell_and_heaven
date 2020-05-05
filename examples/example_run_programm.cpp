
#include "../core_process/processes_controller.h"
#include <iostream>

void example_env_from_map()
{
    std::map<std::string,std::string> e_map;
    e_map["A"] = "B";
    auto env = hh::process::Process_Controllers::c_strigs_environ_from_map(e_map);
    std::cout << std::string(env[0]) << std::endl;
//this is way free env after using
    for(int i = 0; i < e_map.size(); i++)
    {
        free(env[i]);
    }
    free(env);

}

int main()
{
    std::map<std::string,std::string> env = {{"A","B"},{"C","D"}};
    hh::Exe_arg arg(2,std::string("lessecho"),std::string("QWERTY"));
    hh::process::Process_Controllers cont;
    cont.run_program_in_this_process("/usr/bin/lessecho",arg);
    return 0;
}
