#include "psx_signalhandler.h"
#include "../hh_exceptions/hh_exceptions.h"
#include "string.h"
using namespace hh::core_process;

 BaseSignalHandler::BaseSignalHandler(handler_t handl_function, int flag)
{
    __glibc_sigaction.sa_handler = handl_function;
    __glibc_sigaction.sa_flags = flag;
    sigemptyset(&__glibc_sigaction.sa_mask);

}

 BaseSignalHandler::BaseSignalHandler(handler_t handl_function,
                                                       int flag,
                                                       const SetSignals &set)

{
    __glibc_sigaction.sa_handler = handl_function;
    __glibc_sigaction.sa_flags = flag;
    memcpy(&__glibc_sigaction.sa_mask,set.get_c_sigset(), sizeof(__glibc_sigaction.sa_mask));
}

#if defined __USE_POSIX199309 || defined __USE_XOPEN_EXTENDED
 BaseSignalHandler::BaseSignalHandler(psx2_handler_t handl_function, int flag)
 {
     __glibc_sigaction.sa_sigaction = handl_function;
     __glibc_sigaction.sa_flags = flag;
     sigemptyset(&__glibc_sigaction.sa_mask);
 }

 BaseSignalHandler::BaseSignalHandler(psx2_handler_t handl_function, int flag, const SetSignals &set)
 {
     __glibc_sigaction.sa_sigaction = handl_function;
     __glibc_sigaction.sa_flags = flag;
     memcpy(&__glibc_sigaction.sa_mask,set.get_c_sigset(), sizeof(__glibc_sigaction.sa_mask));
 }

#endif

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

}

/*
 BaseSignalHandler VirtualSignalHandler::set_as_handler(const int &signal_code)
{

    auto res = BaseSignalHandler::set_as_handler(signal_code);
    return res;
}
*/


