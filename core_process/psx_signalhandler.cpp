#include "psx_signalhandler.h"
#include "../hh_exceptions/hh_exceptions.h"

using namespace hh::core_process;

 BaseSignalHandler::BaseSignalHandler(handler_t handl_function, int flag)
{
    __glibc_sigaction.sa_handler = handl_function;
    __glibc_sigaction.sa_flags = flag;

}
 BaseSignalHandler::BaseSignalHandler(const struct sigaction &glibc_action)
{
    __glibc_sigaction = glibc_action;
}

 BaseSignalHandler::BaseSignalHandler(const BaseSignalHandler &copy)
{
    __glibc_sigaction = copy.__glibc_sigaction;
}

 BaseSignalHandler::BaseSignalHandler(const BaseSignalHandler&& rv_copy)
{
    __glibc_sigaction = std::move(rv_copy.__glibc_sigaction);
}


 BaseSignalHandler::BaseSignalHandler(handler_t handl_function,
                                                       int flag,
                                                       const SetSignals &set)

{
    __glibc_sigaction.sa_handler = handl_function;
    __glibc_sigaction.sa_flags = flag;
    __glibc_sigaction.sa_mask = *(set.get_c_sigset());
}




void  BaseSignalHandler::
set_mask_handler(const  SetSignals &mask) noexcept
{
    __glibc_sigaction.sa_mask = *(mask.get_c_sigset());
}

 BaseSignalHandler  BaseSignalHandler::set_as_handler(const int& signal_code)
{
    struct sigaction res;
    if(sigaction(signal_code,&__glibc_sigaction,&res) != 0)
    {
        throw hh::ErrnoException();
    }
    return BaseSignalHandler(res);
}

 BaseSignalHandler  get_curent_handler(const int &signal_code)
{
    struct sigaction res;
    if(sigaction(signal_code,NULL,&res) != 0)
    {
        throw hh::ErrnoException();
    }
    return BaseSignalHandler(res);
}

INITT_STATIC_OWNER(VirtualSignalHandler);

VirtualSignalHandler::VirtualSignalHandler(const int& flag, const SetSignals &set) :
    BaseSignalHandler(get_static_action(), flag, set)
{
   //StatFunct::StaticFunctor::set_owner(this);
}

 BaseSignalHandler VirtualSignalHandler::set_as_handler(const int &signal_code)
{

    auto res = BaseSignalHandler::set_as_handler(signal_code);
    return res;
}



