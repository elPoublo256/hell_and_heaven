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
    virtual void action(int signal,
                        const SignalInfo& info,
                        const UserContext& context) = 0;

    virtual void action( int signal, siginfo_t* info_ptr, void* context_ptr) override
    {

      this->action(signal, *((SignalInfo*)info_ptr), *((UserContext*)context_ptr));
    }

};

#define PUBLIC_INFO_VIRTUAL_SIGNAL_HANDLER(CLASS) public hh::core_process::BaseSignalHandler,public hh::smart_functor::Smart_Functor<CLASS, void, int>


class InfoVirtualSignalHandler : public BaseSignalHandler, public SignalInfoFunctor<InfoVirtualSignalHandler>
{
public:
    virtual void action(int signal,
                        const SignalInfo& info,
                        const UserContext& context) = 0;

    InfoVirtualSignalHandler(const int& flag, const SetSignals &set = SetSignals());


  virtual ~InfoVirtualSignalHandler(){}


};

#endif


}
}
