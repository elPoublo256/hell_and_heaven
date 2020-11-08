#pragma once
#include "base_socket.h"
namespace hh {
namespace core_ipc {
namespace psx_socket {



template <sa_family_t Domain, int Proto = 0>
class PSX_Datagramm_Connection : public BaseSocketConnection<Domain,SOCK_DGRAM,Proto>
{
public:


    inline Adress<Domain> get_adress() const { __adress;}

    int psx_send(const void* data, const std::size_t& len, const int& flag) override
    {
        std::cout <<__FUNCTION__ <<std::endl;
        return  __parent_ptr->psx_send_to(data, len, __adress, flag);
    }

     int psx_recv(void* dest, const std::size_t& len, const int& flag) override
    {
        return __parent_ptr->psx_recv_from(dest, len, __adress, flag);
    }
    virtual ~PSX_Datagramm_Connection(){}


    inline const PSX_DataGramSocketBase<Domain,Proto>*
    get_parent_ptr() const
    {return const_cast<PSX_DataGramSocketBase<Domain,Proto>*>(__parent_ptr);}


    PSX_Datagramm_Connection(PSX_DataGramSocketBase<Domain,Proto>* parent,
        const Adress<Domain>& adr) : __adress(adr), __parent_ptr(parent){}


    PSX_DataGramSocketBase<Domain,Proto>* __parent_ptr;

    Adress<Domain> __adress;

};


template <sa_family_t Domain, int Proto = 0>
class PSX_Datagramm_Server :
       public PSX_DataGramSocketBase<Domain,Proto> // create socket

{
public:
    PSX_Datagramm_Server() : PSX_DataGramSocketBase<Domain,Proto>() {}
    virtual std::shared_ptr<PSX_Datagramm_Connection<Domain,Proto>>
    get_connection(const Adress<Domain>& adr)
    {

        //std::shared_ptr<BaseSocketConnection<Domain,SOCK_DGRAM,Proto>>
                //res(new PSX_Datagramm_Connection<Domain,Proto>(this, adr));
        return std::make_shared<PSX_Datagramm_Connection<Domain,Proto>>(this, adr);


    }



};

template <sa_family_t Domain, int Proto = 0>
class PSX_Binded_Datagram_Server : public PSX_Datagramm_Server<Domain,Proto>
{
public:
    PSX_Binded_Datagram_Server(const Adress<Domain>& adr)// : PSX_Datagramm_Server<Domain,Proto>()
    {
        this->psx_bind(adr);
    }


};






}
}
}
