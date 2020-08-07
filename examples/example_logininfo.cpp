#include "../core_user/psx_login.h"
#include <iostream>
int main()
{
    std::cout << "get curent login :"<<hh::core_user::get_curent_user_login() << std::endl;
    auto info = hh::core_user::get_next_log_info();
    std::cout<<"host =" << info.get_host() << std::endl;
    std::cout<<"type = "<<info.get_type() << std::endl;

}
