#include "user.h"
#include <unistd.h>

hh::core_user::User::User(const int &user_id)
{
    errno = 0;
    __uid_t uid(user_id);
    __is_valid = false;
    __pwd = getpwuid(uid);
    if(errno != 0 && __pwd != NULL)
    {
        __is_valid = true;
    }
}

hh::core_user::User::User(const std::string &user_name)
{
    errno = 0;
    std::string name = user_name;
    if(*user_name.rbegin()!='\0')
    {
        name += "\0";
    }
    __is_valid = false;
    __pwd = getpwnam(name.c_str());
    if(errno != 0 && __pwd != NULL)
    {
        __is_valid = true;
    }
}

hh::core_user::User hh::core_user::User::operator =(const User& copy)
{
    __pwd = copy.__pwd;
    __is_valid = copy.__is_valid;
}

hh::core_user::User hh::core_user::User::operator =(User&& rv_copy)
{
    __pwd = std::move(rv_copy.__pwd);
    __is_valid = std::move(rv_copy.__is_valid);
}

bool hh::core_user::check_passward(const User &user, std::string &&passwd)
{
    return false;
}

std::string hh::core_user::User::get_home_directory()
{
    return std::string(__pwd->pw_dir);
}

hh::core_user::Group hh::core_user::User::get_group()
{
    return hh::core_user::Group(__pwd->pw_gid);
}


