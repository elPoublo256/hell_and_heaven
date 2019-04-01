#include "user.h"

hh::user::User::User(const int &user_id)
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

hh::user::User::User(const std::string &user_name)
{
    errno = 0;
    __is_valid = false;
    __pwd = getpwnam(user_name.c_str());
    if(errno != 0 && __pwd != NULL)
    {
        __is_valid = true;
    }
}

hh::user::User hh::user::User::operator =(const User& copy)
{
    __pwd = copy.__pwd;
    __is_valid = copy.__is_valid;
}

hh::user::User hh::user::User::operator =(User&& rv_copy)
{
    __pwd = std::move(rv_copy.__pwd);
    __is_valid = std::move(rv_copy.__is_valid);
}