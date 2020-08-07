#include "group.h"

#include <map>

std::map<int,std::string> __map_gname_gid;

hh::core_user::Group::Group(const std::string &group_name)
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

hh::core_user::Group::Group(const int &gid)
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

hh::core_user::Group hh::core_user::Group::operator =(hh::core_user::Group&& rv_copy)
{

    __group_ptr = std::move(rv_copy.__group_ptr);
    __is_valid = std::move(rv_copy.__is_valid);
    return *this;
}

hh::core_user::Group hh::core_user::Group::operator =(const hh::core_user::Group& copy)
{

    __group_ptr = copy.__group_ptr;
    __is_valid = copy.__is_valid;
    return *this;
}
std::list<std::string> hh::core_user::Group::get_members_names_list()
{
    std::list<std::string> res;
    for(int i = 0; __group_ptr->gr_mem[i] != NULL; i++)
    {
        res.push_back(std::string(__group_ptr->gr_mem[i]));
    }
    return res;
}
