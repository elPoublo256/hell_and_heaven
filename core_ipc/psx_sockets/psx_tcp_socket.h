#pragma once
#include "psx_stream_sockets.h"
namespace  hh{
namespace psx_ip
{

template <sa_family_t Domain = AF_INET>
class PSX_TCP_Socket_Server :
        public hh::core_ipc::psx_socket::PSX_Stream_Socket_Server<Domain,IPPROTO_TCP>
{

};






}
}
