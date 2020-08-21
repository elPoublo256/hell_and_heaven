#pragma once
#include "../../hh_exceptions/hh_exceptions.h"
#include "../psx_base_buffer.h"
namespace hh
{
namespace core_ipc
{



/*!
 * \brief The BaseMesageSender class is a base class for all
 * who can send like POSSIX-Message-Sequence(as sender)
 */
class BaseSender
{
public:
    virtual void send_message(const void* mess_ptr, const std::size_t& len) = 0;
//


};
/*!
 * \brief The BaseMesageSender class is a base class for all
 * who can recv like POSSIX-Message-Sequence(as sender)
 */
class BaseRecever
{
public:
    virtual std::size_t recv_message(const void* mess_ptr, const std::size_t& len) = 0;

};

template <class T>
struct Message : public PSX_TBaseBufer<T>  {};




template <class T>
class BaseMessageSender : public BaseSender
{
public:
    typedef Message<T> Message_t;
     void send_message(const Message_t& mess) const
    {
        BaseSender::send_message(mess.__ptr,mess.__len);
    }
};


template <class T>
class BaseMessageRecever : public BaseRecever
{
public:
    typedef Message<T> Message_t;
    Message_t recv_message()
    {
        Message_t res();
        return res;
    }
};


}
}
