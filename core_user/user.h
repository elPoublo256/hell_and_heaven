#pragma once
#include <pwd.h>
#include <string>
#include "group.h"
namespace hh
{
namespace userspace
{
 class User
 {
 private:
     passwd* __pwd;
     bool __is_valid;
 public:
     //! last char should be '\0'
     User(const std::string& user_name);
     User(const int& user_id);
     User(const User& copy) = default;
     User(User&& rv_copy) = default;
     User operator = (const User& copy);
     User operator = (User&& rv_copy);
     friend bool check_passward(const User& user, std::string&& passwd);
     std::string get_home_directory();
     hh::userspace::Group get_group();
     inline auto get_passward(){return std::string(__pwd->pw_passwd);}
     inline auto have_a_passward(){return (std::string{'x'} == get_passward());}
     uid_t get_user_id() const {return __pwd->pw_uid;}
     gid_t get_group_id() const {return __pwd->pw_gid;}



 };
 bool check_passward(const User& user, std::string&& passwd);

}
}
