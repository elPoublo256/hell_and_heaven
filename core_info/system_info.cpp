#include "system_info.h"
#include <sys/utsname.h>

bool __is_louded = false;
utsname __geted_utsname;

void __load_utsname_with_check()
{
    if(!__is_louded)
    {
        auto err = uname(&__geted_utsname);
        if(err == -1)
        {
            throw hh::ErrnoException();
        }
        else
        {
            __is_louded = true;
        }
    }
}



#ifdef _GNU_SOURCE
std::string hh::core_info::system_info::get_domain_name()
{
    __load_utsname_with_check();
    return std::string(__geted_utsname.domainname);
}
#endif
std::string hh::core_info::system_info::get_mashime()
{
    __load_utsname_with_check();
    return std::string(__geted_utsname.machine);

}
std::string hh::core_info::system_info::get_host_name()
{
    __load_utsname_with_check();
    return std::string(__geted_utsname.nodename);

}
std::string hh::core_info::system_info::get_relese_OS()
{
    __load_utsname_with_check();
    return std::string(__geted_utsname.release);

}
std::string hh::core_info::system_info::get_sys_name()
{
    __load_utsname_with_check();
    return std::string(__geted_utsname.sysname);

}
std::string hh::core_info::system_info::get_version_OS()
{
    __load_utsname_with_check();
    return std::string(__geted_utsname.version);

}




