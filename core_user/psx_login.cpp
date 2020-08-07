#include "psx_login.h"
#include "unistd.h"



static auto get_cpp_value(char* vall_c_str,const int &max_size)
{
    std::string res;
    for(int i = 0; i < max_size; i++)
    {
        if( *(vall_c_str + i) == char(NULL))
        {
           return std::string(vall_c_str, i);

        }
    }
    return std::string();
}

hh::core_user::PSX_Login_Info::PSX_Login_Info(const int &type)  : utmpx()
{
 ut_type = type;
}


hh::core_user::PSX_Login_Info::PSX_Login_Info(const utmpx *ptr) : utmpx(*ptr)
{

}

std::string hh::core_user::PSX_Login_Info::get_host() const
{

    return get_cpp_value((char*)ut_host,__UT_HOSTSIZE);
}

hh::core_user::PSX_Login_Info&& hh::core_user::get_next_log_info()
{
    auto ptr = getutxent();
    if(ptr == NULL)
    {
        throw PSX_Login_Error("getutxent return NULL");
    }
    return  std::move(PSX_Login_Info(ptr));
}
