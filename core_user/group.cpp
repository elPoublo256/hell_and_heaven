#include "group.h"

#include <map>

std::map<int,std::string> __map_gname_gid;

hh::user::Group::Group(const std::string &group_name)
{
    __is_valid =false;
    errno = 0;
    __group_ptr = getgrnam(group_name.c_str());
    if(errno == 0 && __group_ptr != NULL)
    {
        __map_gname_gid[__group_ptr->gr_gid] = std::string(__group_ptr->gr_name);
      __is_valid = true;
    }
}

hh::user::Group::Group(const int &gid)
{
    errno = 0;
    __is_valid = false;
    gid_t __gid(gid);
    __group_ptr = getgrgid(__gid);
    if(errno == 0 && __group_ptr != NULL)
    {
        // не соответсвие SUSv3
        __map_gname_gid[__group_ptr->gr_gid] = std::string(__group_ptr->gr_name);
        __is_valid = true;
    }

}

hh::user::Group hh::user::Group::operator =(hh::user::Group&& rv_copy)
{

    __group_ptr = std::move(rv_copy.__group_ptr);
    __is_valid = std::move(rv_copy.__is_valid);
    return *this;
}

hh::user::Group hh::user::Group::operator =(const hh::user::Group& copy)
{

    __group_ptr = copy.__group_ptr;
    __is_valid = copy.__is_valid;
    return *this;
}

