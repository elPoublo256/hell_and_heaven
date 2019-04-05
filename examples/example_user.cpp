#include "../core_user/user.h"
#include <stdlib.h>
#include<string>
#include <iostream>
int main()
{
	std::string username(getenv("LOGNAME"));
	std::cout << "username is "<<username<<std::endl;
    hh::userspace::User user(username);
    auto dir = user.get_home_directory();
    std::cout<<"user home directory is " << dir <<std::endl;
    std::cout<<"user groupname is "<<user.get_group().get_group_name()<<std::endl;
    auto grup = user.get_group();
    auto member_list = grup.get_members_names_list();
    for(auto s : member_list)
    {
        std::cout << "user "<<s<<"in group "<<grup.get_group_name();
    }
    std::cout<<"user passward is "<<user.get_passward();

	return 0;


}
