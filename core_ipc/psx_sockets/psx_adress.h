#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <string>
#include <strings.h>
#include <memory.h>
namespace hh {
namespace core_ipc {
namespace psx_socket {

template <sa_family_t Domain>
class Adress
{
protected:
    std::size_t __len;
    sockaddr* __adr;
public:
     std::size_t get_len() const {return __len;}
     sockaddr* get_sockaddr() const {return __adr;}
    Adress(sockaddr* src, std::size_t len) : __len(len)
    {__adr = (sockaddr*)malloc(__len); memcpy(__adr,src,__len);}

    Adress(const Adress<Domain>& copy)
        : Adress(copy.get_sockaddr(), copy.get_len()) {}

    Adress(Adress<Domain>&& rv_copy) : __len(rv_copy.__len), __adr(rv_copy.__adr) {}
    Adress(){}

    virtual ~Adress(){}
};



}
}
}
