#pragma once
#include "psx_signalhandler.h"

namespace hh {
namespace core_process {
#if defined __USE_POSIX199309 || defined __USE_XOPEN_EXTENDED
class SignalInfo : public siginfo_t
{
  //TODO make getters
};

class UserContext : public ucontext_t
{

};

template <class SelfType>
class SignalInfoFunctor :
public hh::smart_functor::Smart_Functor<SelfType, void, int, siginfo_t*, void*>
{
 public:
    typedef hh::smart_functor::StaticFunctor<SelfType, void, int, siginfo_t*, void*> StatFunct;
    void set_owner(SelfType* ptr){StatFunct::set_owner(ptr) ;}
    virtual void info_action(int signal,
                        const SignalInfo& info,
                        const UserContext& context) = 0;

    virtual void action( int signal, siginfo_t* info_ptr, void* context_ptr) override
    {

      this->info_action(signal, *((SignalInfo*)info_ptr), *((UserContext*)context_ptr));
    }

    SignalInfoFunctor(){}

};


class PSX2_BaseSignalHandler : public PSX1_BaseSignalHandler
{
  public:
    PSX2_BaseSignalHandler(){}
    PSX2_BaseSignalHandler(psx2_handler_t handl_function, int flag = 0) : PSX1_BaseSignalHandler(handl_function,flag){}
    PSX2_BaseSignalHandler(const PSX1_BaseSignalHandler& copy) = delete;
    PSX2_BaseSignalHandler(const PSX1_BaseSignalHandler&& rv_copy) : PSX1_BaseSignalHandler(rv_copy){}
    PSX2_BaseSignalHandler(handler_t handl_function, int flag, const SetSignals& set) = delete;
    PSX2_BaseSignalHandler(void(*info_handler)(int, const SignalInfo&, const UserContext&),
                           int flag, const SetSignals& s);




};


#define PUBLIC_INFO_VIRTUAL_SIGNAL_HANDLER(CLASS) public hh::core_process::PSX2_BaseSignalHandler,public hh::smart_functor::Smart_Functor<CLASS, void, int>


class InfoVirtualSignalHandler : public PSX2_BaseSignalHandler, public SignalInfoFunctor<InfoVirtualSignalHandler>
{
public:
    virtual void info_action(int signal,
                         const SignalInfo& info,
                        const UserContext& context) = 0;

    InfoVirtualSignalHandler(const int& flag, const SetSignals &set = SetSignals());


  virtual ~InfoVirtualSignalHandler(){}


};

#endif


}
}
