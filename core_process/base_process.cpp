#include "base_process.h"
#include "../hh_exceptions/hh_exceptions.h"
extern char **environ;
hh::process::Base_Process::Base_Process()
{
  //----loud all environs to map -----//
  load_map_eniron();
}
void hh::process::Base_Process::load_map_eniron() noexcept
{
    for(int i = 0; environ[i] != NULL; i++)
    {
      std::string str_env(environ[i]);
      auto pos_eq = str_env.find_first_of('=');
      auto key = str_env.substr(0, pos_eq-1);
      auto val = str_env.substr(pos_eq+1);
      __environ_map[key] = val;

    }
}

void hh::process::Base_Process::prepare_before_start()
{
    __environ_map.clear();
    load_map_eniron();
}


std::string&& hh::process::Base_Process::susv3_get_eniron(const std::string &key) const
{
    //std::string res{'\0'};
    auto it_res = __environ_map.find(key);
    if(it_res != __environ_map.end())
    {
        return std::move(std::string(key + std::string{'='}+it_res->second));
    }
    else
    {
        return std::move(std::string{'\0'});
    }
}

std::string&& hh::process::Base_Process::get_environ(const std::string &key) const
{
    auto it_res = __environ_map.find(key);
    if(it_res != __environ_map.end())
    {
        return std::move(std::string(it_res->second));
    }
    else
    {
        return std::move(std::string{});
    }
}

void hh::process::Base_Process::set_environ(const std::string &key, const std::string &value,
                                            const int& overflow)
{
    errno = 0;
    auto res = setenv(key.c_str(), value.c_str(), overflow);
    if(res)
    {
        __environ_map[key] = value;
    }
    else
    {
        throw hh::ErrnoException();
    }
}

void hh::process::Base_Process::unset_environ(const std::string key)
{
    errno = 0;
    auto it_res = __environ_map.find(key);
    if(it_res != __environ_map.end())
    {
        auto res = unsetenv(key.c_str());
        if(res)
        {
            throw hh::ErrnoException();
        }
    }
}

void hh::process::Base_Process::clean_environ()
{
    for(auto s : __environ_map)
    {
        this->unset_environ(s.first);
    }
}




