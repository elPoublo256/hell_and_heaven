#pragma once
#include "psx_adress.h"
#include <string>
#include <stdexcept>
namespace  hh{
namespace psx_ip
{

class PSX_IP_Adress_Error : public std::runtime_error
{
  public:
    PSX_IP_Adress_Error(const char* str);
    PSX_IP_Adress_Error(const std::string& str);
};

class PSX_IP_Adress : public hh::core_ipc::psx_socket::Adress<AF_INET>
{
public:
 PSX_IP_Adress(const char* str_adr, const int& port);
 PSX_IP_Adress(const std::string& str_adr, const int& port){}

};

}
}
