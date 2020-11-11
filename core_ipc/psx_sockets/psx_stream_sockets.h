#pragma once

#include "base_socket.h"
namespace hh {
namespace core_ipc {
namespace psx_socket {

template <sa_family_t Domain, int Proto>
class PSX_BaseStreamSocket : public PSX_Base_Socket<Domain,SOCK_STREAM,Proto>
{
public:
    PSX_BaseStreamSocket() : PSX_Base_Socket<Domain,SOCK_STREAM,Proto>(){}

    inline void psx_listen(const int& backlog) const
    {
        if(listen(this->get_file_discriptror(), backlog))
        {
            throw PSX_Socket_Error("error listen");
        }
    }


    PSX_BaseStreamSocket(const Adress<Domain>& adr_bind) :
        PSX_Base_Socket<Domain,SOCK_STREAM,Proto>() {this->psx_bind(adr_bind);}

    inline bool psx_noex_connect(const struct sockadr* adr, const std::size_t &adr_len) noexcept
    {
        return connect(this->get_file_discriptror(),adr, adr_len) == 0;
    }

     void psx_connect(struct sockadr* adr, const std::size_t &adr_len)
    {
        if(connect(this->get_file_discriptror(),adr, adr_len) != 0)
        {
            throw PSX_Socket_Error("error connection");
        }
    }

   void psx_connect(const Adress<Domain>& adr)
   {
       if(connect(this->get_file_discriptror(),adr.get_sockaddr(), adr.get_len()) != 0)
       {
           throw PSX_Socket_Error("error connection");
       }
   }

};

template <sa_family_t Domain, int Proto>
class PSX_Stream_Soket_Server;

template <sa_family_t Domain, int Proto>
class PSX_Stream_Socket_Connection : public BaseSocketConnection<Domain, SOCK_STREAM,Proto>,
                                     public BaseFDReaderWriter
{

public:

    PSX_Stream_Socket_Connection() : BaseFDReaderWriter(){}
    PSX_Stream_Socket_Connection(const int& fd) : BaseFDReaderWriter(fd){}
    PSX_Stream_Socket_Connection(const PSX_Stream_Socket_Connection& cop) = delete;
    PSX_Stream_Socket_Connection(PSX_Stream_Socket_Connection&& rv_copy) : BaseFDReaderWriter(std::move(rv_copy)){}

    virtual int psx_send(const void* data, const std::size_t& len, const int& flag)
    {
        auto res = send(this->get_file_discriptror(),data,len,flag);
         if(res < 0)
         {
             throw PSX_Socket_Error("error send");
         }
         return res;
    }
    virtual int psx_recv(void* dest, const std::size_t& len, const int& flag)
    {
        auto res = recv(this->get_file_discriptror(),dest,len,flag);
         if(res < 0)
         {
             throw PSX_Socket_Error("error send");
         }
         return res;
    }
};


template <sa_family_t Domain, int Proto>
class PSX_Stream_Socket_Server : public PSX_BaseStreamSocket<Domain,Proto>
{
public:
    PSX_Stream_Socket_Connection<Domain, Proto> get_connection()
    {

        auto fd = accept(this->get_file_discriptror(),NULL,NULL);
        if(fd < 0)
        {
            throw PSX_Socket_Error("error accept");
        }
        else
        {
            return PSX_Stream_Socket_Connection<Domain, Proto>(fd);
        }
    }
    PSX_Stream_Socket_Server(const Adress<Domain>& adr) : PSX_BaseStreamSocket<Domain,Proto>()
    {
        this->psx_bind(adr);
    }

    PSX_Stream_Socket_Server(const Adress<Domain>& adr , const std::size_t& num_connect)
        : PSX_BaseStreamSocket<Domain,Proto>()
    {
        this->psx_bind(adr);
        this->psx_listen(num_connect);
    }
};


template <sa_family_t Domain, int Proto>
class PSX_Stream_Socket_Client : public PSX_BaseStreamSocket<Domain,Proto>
{
public:
    PSX_Stream_Socket_Client(const Adress<Domain>& connect_adr) :
        PSX_BaseStreamSocket<Domain,Proto>()
    {
        this->psx_connect(connect_adr);
    }

    virtual int psx_send(const void* data, const std::size_t& len, const int& flag)
    {
        auto res = send(this->get_file_discriptror(),data,len,flag);
         if(res < 0)
         {
             throw PSX_Socket_Error("error send");
         }
         return res;
    }
    virtual int psx_recv(void* dest, const std::size_t& len, const int& flag)
    {
        auto res = recv(this->get_file_discriptror(),dest,len,flag);
         if(res < 0)
         {
             throw PSX_Socket_Error("error send");
         }
         return res;
    }


};




}
}
}
