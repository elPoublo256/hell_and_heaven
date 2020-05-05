#pragma once
#include "psx_signals.h"
#include <functional>
#include "static_hanler.h"
#include <exception>
//#include "psx_alterstack.h"
namespace hh {
namespace core_process {






class PSX1_BaseSignalHandler
{
  public:

        typedef decltype(sigaction::sa_handler) handler_t;



    PSX1_BaseSignalHandler(){}

    PSX1_BaseSignalHandler(const struct sigaction& glibc_action);
    PSX1_BaseSignalHandler(handler_t handl_function, int flag = 0);

#if defined __USE_POSIX199309 || defined __USE_XOPEN_EXTENDED
typedef decltype(sigaction::sa_sigaction) psx2_handler_t;
PSX1_BaseSignalHandler(psx2_handler_t handl_function, int flag = 0);
///DO NOT FORGET SET SA_INFO for getting info of signal
PSX1_BaseSignalHandler(psx2_handler_t handl_function, int flag, const SetSignals& set);
#endif
    PSX1_BaseSignalHandler(const PSX1_BaseSignalHandler& copy);
    PSX1_BaseSignalHandler(const PSX1_BaseSignalHandler&& rv_copy);
    PSX1_BaseSignalHandler(handler_t handl_function, int flag, const SetSignals& set);
    void operator = (const PSX1_BaseSignalHandler& copy){__glibc_sigaction = copy.__glibc_sigaction;}
    auto get_glib_sigaction() noexcept {return __glibc_sigaction;}
    auto get_glib_sigaction_ptr() noexcept {return &__glibc_sigaction;}
    void set_mask_handler(const hh::core_process::SetSignals& mask) noexcept;

    virtual PSX1_BaseSignalHandler set_as_handler(const int& signal_code);
    virtual ~PSX1_BaseSignalHandler(){}
    SetSignals get_masck();

  protected:
    struct sigaction __glibc_sigaction;
    int __hand_signal = -1;

};

PSX1_BaseSignalHandler get_curent_handler(const int& signal_code);

class RAI_SignalHandler : public PSX1_BaseSignalHandler
{
protected:
    PSX1_BaseSignalHandler handler_before;
    int signal;
public:

    RAI_SignalHandler(handler_t handler,
                      const int& signal_code,
                      const int& flag, const SetSignals set) :
        PSX1_BaseSignalHandler(handler, flag, set)
    {
        handler_before = this->set_as_handler(signal_code);
        signal = signal_code;
    }

    ///USE glibc sigatcion for unposible throwing exception in distructor
    ~RAI_SignalHandler(){sigaction(signal, handler_before.get_glib_sigaction_ptr(),&__glibc_sigaction);}
};





#define PUBLIC_VIRTUAL_SIGNAL_HANDLER(CLASS) public hh::core_process::PSX1_BaseSignalHandler,  public hh::smart_functor::Smart_Functor<CLASS, void, int>




class VirtualSignalHandler : public PSX1_BaseSignalHandler, public hh::smart_functor::Smart_Functor<VirtualSignalHandler, void, int>
{
public:
//virtual void action(int a) override { return void();}
  VirtualSignalHandler(const int& flag = 0, const SetSignals& set = SetSignals());
  //BaseSignalHandler set_as_handler(const int &signal_code);
  virtual ~VirtualSignalHandler(){}


};













}
}
