#include "base_process.h"
#include "../hh_exceptions/hh_exceptions.h"
extern char **environ;
hh::process::Base_Process::Base_Process()
{
  //----loud all environs to map -----//
  load_map_environ();
  load_all_id();

}
void hh::process::Base_Process::load_map_environ() noexcept
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
    load_map_environ();
}


std::string&& hh::process::Base_Process::susv3_get_environ(const std::string &key) const
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


void hh::process::Base_Process::load_all_id() noexcept
{
#ifdef __linux__
  __gid_t gr,ge,gs; __uid_t ur,ue,us;
  getresgid(&gr, &ge, &gs);
  getresuid(&ur,&ue, &us);

  id = Process_ID{int(getpid()), int(gr),
          int(ge), int(ur), int(ue), int(gs), int(us)};

#else
    id = Process_ID{int(getpid()), int(getgid()),
            int(getegid()), int(getuid()), int(geteuid())};
#endif
}


void hh::process::Base_Process::set_real_group_id(const int &new_gid)
{
    errno = 0;
    if(setregid(new_gid, id.group_id_effect) < 0)
    {
        throw hh::PermissionErr();
    }


    id.group_id_real = getgid();

}
void hh::process::Base_Process::set_effective_group_id(const int &new_gid)
{
    errno = 0;
    if(setegid(new_gid) < 0)
    {
        throw hh::PermissionErr();
    }
    id.group_id_effect = getgid();

}
void hh::process::Base_Process::set_effective_user_id(const int &new_uid)
{
    if(seteuid(new_uid) < 0)
    {
        throw hh::PermissionErr();
    }

    id.user_id_effect = getuid();

}

void hh::process::Base_Process::set_real_user_id(const int &new_uid)
{
    if(setreuid(new_uid, id.user_id_effect) < 0)
    {
        throw hh::PermissionErr();
    }

    id.user_id_real = getuid();

}

#ifdef __linux__
void hh::process::Base_Process::set_all_group_id(const int &r_gid, const int &e_gid, const int &s_gid)
{
    if(setresgid(r_gid,e_gid,s_gid) < 0)
    {
        throw PermissionErr();
    }
}

void hh::process::Base_Process::set_all_user_id(const int &r_gid, const int &e_gid, const int &s_gid)
{
    if(setresuid(r_gid,e_gid,s_gid) < 0)
    {
        throw PermissionErr();
    }
}
#endif
