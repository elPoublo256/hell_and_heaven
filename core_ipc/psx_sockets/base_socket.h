#pragma once
#include <sys/socket.h>
#include "../../core_base/psx_base_file.h"
#include "../../hh_exceptions/hh_exceptions.h"
#include "psx_adress.h"
#include <iostream>
#define PSX_BASE_SIZE_RECV 1024
namespace hh {
namespace core_ipc {
namespace psx_socket {
/*!
 * \brief The PSX_Socket_Error class - Error in warking with socket
 */
class PSX_Socket_Error : public hh::ErrnoException
{
public:
    PSX_Socket_Error() : hh::ErrnoException(){}
    PSX_Socket_Error(const char* err) : hh::ErrnoException(err){}
};


/*!
 * \brief The PSX_Base_Socket class <sa_family_t Domain,int Type  ,int Proto = 0>
 * wich create a hh::BaseFDReaderWriter with file-descripaor as result 'int socket(Domain,Type,Proto)
 */
template <sa_family_t Domain,int Type  ,int Proto = 0>
class PSX_Base_Socket : public hh::BaseFDReaderWriter
{
public:
    typedef Adress<Domain> psx_adress_t;
    /*!
     * \brief PSX_Base_Socket
     * create a hh::BaseFDReaderWriter with file-descripaor as result 'int socket(Domain,Type,Proto)
     * \throw PSX_Socket_Error if result of 'int socket(Domain,Type,Proto)' return -1
     */
    PSX_Base_Socket(){this->__fd = socket(Domain,Type, Proto);
                      if(__fd <= 0)
                      {
                          throw PSX_Socket_Error("error create socket");
                      }}
    virtual ~PSX_Base_Socket(){}

    ///bind curenet socket to adress setat in C-style
    virtual void psx_bind(sockaddr* addres,const socklen_t& len )
    {
        if(bind(this->__fd,addres,len) != 0)
        {
            throw  PSX_Socket_Error("error bind socket");
        }
    }

    ///bind curent socket to adress seted in HH-style
    virtual void psx_bind(const psx_adress_t& adress)
    {
        psx_bind(adress.get_sockaddr(), adress.get_len());
    }




};

/*!
* \brief The PSX_DataGramSocketBase class
* base calss of datagramm sockets
        */

template <sa_family_t Domain, int Proto = 0>
class PSX_DataGramSocketBase : public PSX_Base_Socket<Domain,SOCK_DGRAM, Proto>
{
public:
    typedef  PSX_Base_Socket<Domain,SOCK_DGRAM, Proto> parent_t;
    PSX_DataGramSocketBase() : PSX_Base_Socket<Domain,SOCK_DGRAM, Proto>() {}
    ~PSX_DataGramSocketBase(){}
     int psx_send_to(const void* data, const std::size_t& len, sockaddr* addres, std::size_t adr_len, int flag)
    {
        std::cout<<__FUNCTION__<<std::endl;
        auto res = sendto(this->get_file_discriptror(),data,len, flag,addres,adr_len);
        if(res == -1)
        {
            throw PSX_Socket_Error("error psx_send_to");
        }
        return res;
    }

    int psx_send_to(const void* data,
                    const std::size_t& len,
                    const Adress<Domain>& adres, const int& flag)
    {
        return psx_send_to(data, len, adres.get_sockaddr(), adres.get_len(), flag);
    }

    inline int psx_recv_from(void* dest,
                             const std::size_t& len,
                             sockaddr* adress,
                             const std::size_t& adr_len,
                             const int& flag)
    {
        socklen_t __len = adr_len;
        auto res = recvfrom(this->get_file_discriptror(), dest, len, flag, adress, &__len);
        if(res < 0)
        {
            throw  PSX_Socket_Error("error recv from");
        }

        return res;
    }







    int psx_recv_from(void* dest,
                      const std::size_t& len,
                      const Adress<Domain>& adr,
                      const int& flag)
    {
        return psx_recv_from(dest,len, adr.get_sockaddr(), adr.get_len(), flag);
    }

    inline PSX_Base_Bufer psx_recv_from(sockaddr* addres, std::size_t adr_len, int flag)
    {
        PSX_Base_Bufer res(__resv_size);
        auto s = recvfrom(this->get_file_discriptror(),res.get_p(),__resv_size,flag,addres,adr_len);
        if(s < 0)
        {
            throw PSX_Socket_Error("error recv_from : ");
        }
        res.resize(s);
        return res;
    }

protected:

    std::size_t __resv_size = PSX_BASE_SIZE_RECV;



};

template <sa_family_t Domain, int Type, int Proto = 0>
class BaseSocketConnection
{
public:
    BaseSocketConnection(){}
    virtual int psx_send(const void* data, const std::size_t& len, const int& flag) = 0;
    virtual int psx_recv(void* desat, const std::size_t& len, const int& flag) = 0;
    virtual ~BaseSocketConnection(){}

};




















}
}
}
