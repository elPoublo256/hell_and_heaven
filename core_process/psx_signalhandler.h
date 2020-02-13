#pragma once
#include "psx_signals.h"
#include <functional>
#include "static_hanler.h"
#include <exception>
#include "psx_alterstack.h"
namespace hh {
namespace core_process {






class BaseSignalHandler
{
  public:

        typedef decltype(sigaction::sa_handler) handler_t;



    BaseSignalHandler(){}

    BaseSignalHandler(const struct sigaction& glibc_action);
    BaseSignalHandler(handler_t handl_function, int flag = 0);

#if defined __USE_POSIX199309 || defined __USE_XOPEN_EXTENDED
typedef decltype(sigaction::sa_sigaction) psx2_handler_t;
BaseSignalHandler(psx2_handler_t handl_function, int flag = 0);
BaseSignalHandler(psx2_handler_t handl_function, int flag, const SetSignals& set);
#endif
    BaseSignalHandler(const BaseSignalHandler& copy);
    BaseSignalHandler(const BaseSignalHandler&& rv_copy);
    BaseSignalHandler(handler_t handl_function, int flag, const SetSignals& set);
    void operator = (const BaseSignalHandler& copy){__glibc_sigaction = copy.__glibc_sigaction;}
    auto get_glib_sigaction() noexcept {return __glibc_sigaction;}
    auto get_glib_sigaction_ptr() noexcept {return &__glibc_sigaction;}
    void set_mask_handler(const hh::core_process::SetSignals& mask) noexcept;

    virtual BaseSignalHandler set_as_handler(const int& signal_code);
    virtual ~BaseSignalHandler(){}
    SetSignals get_masck();

  protected:
    struct sigaction __glibc_sigaction;
    int __hand_signal = -1;

};

BaseSignalHandler get_curent_handler(const int& signal_code);

class RAI_SignalHandler : public BaseSignalHandler
{
protected:
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





#define PUBLIC_VIRTUAL_SIGNAL_HANDLER(CLASS) public hh::core_process::BaseSignalHandler,  public hh::smart_functor::Smart_Functor<CLASS, void, int>




class VirtualSignalHandler : public BaseSignalHandler, public hh::smart_functor::Smart_Functor<VirtualSignalHandler, void, int>
{
public:
//virtual void action(int a) override { return void();}
  VirtualSignalHandler(const int& flag = 0, const SetSignals& set = SetSignals());
  BaseSignalHandler set_as_handler(const int &signal_code);
  virtual ~VirtualSignalHandler(){}


};













}
}
