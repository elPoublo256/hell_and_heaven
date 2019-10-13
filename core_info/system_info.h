#pragma once
#include <string>
#include <unistd.h>
#include"../hh_exceptions/hh_exceptions.h"
namespace hh {
namespace core_info {
namespace system_info {
std::string get_sys_name();
std::string get_host_name();
std::string get_relese_OS();
std::string get_version_OS();
std::string get_mashime();
#ifdef _GNU_SOURCE
std::string get_domain_name();
void set_domain_name(const std::string& domainname);
#endif
}

void set_host_name(const std::string& hostname);



inline auto get_system_limit(const int& possix_limit_name) noexcept
{
    return sysconf(possix_limit_name);
}

template <decltype(_SC_ARG_MAX) limit>
std::size_t get_limit()
{
 errno = 0;
 auto res = sysconf(limit);
 if(res == -1)
 {
     throw hh::ErrnoException();
 }
 return res;
}

}

}
