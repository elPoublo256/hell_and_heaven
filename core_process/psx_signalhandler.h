#pragma once
#include "psx_signals.h"
#include <functional>

#include <exception>

namespace hh {
namespace core_process {


template <class HandlerType>
void static_action(int s){HandlerType h;}


class BaseSignalHandler
{
  public:
    typedef decltype(sigaction::sa_handler) handler_t;
    BaseSignalHandler(){}
    BaseSignalHandler(const struct sigaction& glibc_action);
    BaseSignalHandler(handler_t handl_function, int flag = 0);
    BaseSignalHandler(const BaseSignalHandler& copy);
    BaseSignalHandler(const BaseSignalHandler&& rv_copy);
    BaseSignalHandler(handler_t handl_function, int flag, const SetSignals& set);
    void operator = (const BaseSignalHandler& copy){__glibc_sigaction = copy.__glibc_sigaction;}
    auto get_glib_sigaction() noexcept {return __glibc_sigaction;}
    auto get_glib_sigaction_ptr() noexcept {return &__glibc_sigaction;}
    void set_mask_handler(const hh::core_process::SetSignals& mask) noexcept;

    BaseSignalHandler set_as_handler(const int& signal_code);
    virtual ~BaseSignalHandler(){}
    SetSignals get_masck();

  protected:
    struct sigaction __glibc_sigaction;
    int __hand_signal = -1;

};

BaseSignalHandler get_curent_handler(const int& signal_code);

class RAI_SignalHandler : public BaseSignalHandler
{
private:
    BaseSignalHandler handler_before;
    int signal;
public:

    RAI_SignalHandler(handler_t handler,
                      const int& signal_code,
                      const int& flag, const SetSignals set) :
        BaseSignalHandler(handler, flag, set)
    {
        handler_before = this->set_as_handler(signal_code);
        signal = signal_code;
    }

    ///USE glibc sigatcion for unposible throwing exception in distructor
    ~RAI_SignalHandler(){sigaction(signal, handler_before.get_glib_sigaction_ptr(),&__glibc_sigaction);}
};











///this classes no usfall but i like this idea
///this class is like a lambda [](...Args)->ResType{Handler h; return h.handl();}
template <class Handler, typename ResType, typename... Args>
class StaticHandler
{
   static ResType action(Args ...args){Handler h; return h.handl();}
};


 #define VIRTUAL_SIGNAL_HANDLER typedef StaticHandler<selftype, void,int> static_handler;
class VirtualSignalHandler : public BaseSignalHandler
{
public:
    class Exception : public std::runtime_error
    {
        Exception(const std::string& s) : std::runtime_error(s){}
    };
    typedef VirtualSignalHandler selftype;
    VIRTUAL_SIGNAL_HANDLER
    virtual void handl(int signal){}
    virtual ~VirtualSignalHandler();

    VirtualSignalHandler(){}
    //std::shared_ptr<selftype> static_handler::owner = std::make_shared<selftype>();
protected:
    VirtualSignalHandler(const int& flag, const SetSignals& set_signals);
};




}
}
