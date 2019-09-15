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
#include "exe_arg.h"
namespace hh {

namespace process {

class Base_Process
{
  public:
    Base_Process();
    virtual ~Base_Process();
    typedef int pid_type;
    typedef std::map<std::string,std::string>::iterator envir_iter_t;
    typedef std::map<std::string,std::string>::const_iterator c_envir_iter_t;

    virtual void start(hh::Exe_arg &arg);

    std::string&& susv3_get_eniron(const std::string& key) const;//return "key=value"
    std::string&& get_environ(const std::string& key) const;

    void set_environ(const std::string& key, const std::string& value,
                     const int& overflow = 0);
    void unset_environ(const std::string key);

    void clean_environ();
    inline auto get_all_envir(){return std::pair<c_envir_iter_t,
                c_envir_iter_t>{__environ_map.begin(),__environ_map.end()};}
 private:
    std::map<std::string,std::string> __environ_map;

    pid_type pid;
 protected:
    virtual void prepare_before_start();
    virtual void run(hh::Exe_arg &arg);
    virtual int main(int argv, char* argc[]) = 0;
    void load_map_environ() noexcept;

};

}

}
