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

#define PUBLIC_INFO_VIRTUAL_SIGNAL_HANDLER(CLASS) public hh::core_process::BaseSignalHandler,public hh::smart_functor::Smart_Functor<CLASS, void, int>


class InfoVirtualSignalHandler : public BaseSignalHandler, public SignalInfoFunctor<InfoVirtualSignalHandler>
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
