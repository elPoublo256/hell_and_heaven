#include "psx_ip_adress.h"
#include <string.h>
#include <arpa/inet.h>

hh::psx_ip::PSX_IP_Adress_Error::PSX_IP_Adress_Error(const char* str) :
    std::runtime_error(str)
{

}

hh::psx_ip::PSX_IP_Adress_Error::PSX_IP_Adress_Error(const std::string& str) :
    std::runtime_error(str)
{

}



hh::psx_ip::PSX_IP_Adress::PSX_IP_Adress(const char* str_adr, const int& port)
{
    __len = sizeof (sockaddr_in);
    __adr = (sockaddr*)malloc(__len);
    memset(__adr, 0, __len);
    __adr->sa_family = AF_INET;
    auto p_adr = (sockaddr_in*) __adr;
    p_adr->sin_port = htons(port);
    p_adr->sin_addr.s_addr = inet_addr(str_adr);
    if(p_adr->sin_addr.s_addr == INADDR_NONE)
    {
        throw hh::psx_ip::PSX_IP_Adress_Error(std::string("bad adress: ")
                                              + std::string(str_adr));
    }
}
