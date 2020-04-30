#include "psx_signalhandler.h"
#include "../hh_exceptions/hh_exceptions.h"
#include "string.h"
using namespace hh::core_process;

 PSX1_BaseSignalHandler::PSX1_BaseSignalHandler(handler_t handl_function, int flag)
{
    __glibc_sigaction.sa_handler = handl_function;
    __glibc_sigaction.sa_flags = flag;
    sigemptyset(&__glibc_sigaction.sa_mask);

}

 PSX1_BaseSignalHandler::PSX1_BaseSignalHandler(handler_t handl_function,
                                                       int flag,
                                                       const SetSignals &set)

{
    __glibc_sigaction.sa_handler = handl_function;
    __glibc_sigaction.sa_flags = flag;
    memcpy(&__glibc_sigaction.sa_mask,set.get_c_sigset(), sizeof(__glibc_sigaction.sa_mask));
}

#if defined __USE_POSIX199309 || defined __USE_XOPEN_EXTENDED
 PSX1_BaseSignalHandler::PSX1_BaseSignalHandler(psx2_handler_t handl_function, int flag)
 {
     __glibc_sigaction.sa_sigaction = handl_function;
     __glibc_sigaction.sa_flags = flag;
     sigemptyset(&__glibc_sigaction.sa_mask);
 }

 PSX1_BaseSignalHandler::PSX1_BaseSignalHandler(psx2_handler_t handl_function, int flag, const SetSignals &set)
 {
     __glibc_sigaction.sa_sigaction = handl_function;
     __glibc_sigaction.sa_flags = flag;
     memcpy(&__glibc_sigaction.sa_mask,set.get_c_sigset(), sizeof(__glibc_sigaction.sa_mask));
 }

#endif

 PSX1_BaseSignalHandler::PSX1_BaseSignalHandler(const struct sigaction &glibc_action)
{
    __glibc_sigaction = glibc_action;
}

 PSX1_BaseSignalHandler::PSX1_BaseSignalHandler(const PSX1_BaseSignalHandler &copy)
{
    __glibc_sigaction = copy.__glibc_sigaction;
}

 PSX1_BaseSignalHandler::PSX1_BaseSignalHandler(const PSX1_BaseSignalHandler&& rv_copy)
{
    __glibc_sigaction = std::move(rv_copy.__glibc_sigaction);
}






void  PSX1_BaseSignalHandler::
set_mask_handler(const  SetSignals &mask) noexcept
{
    __glibc_sigaction.sa_mask = *(mask.get_c_sigset());
}

 PSX1_BaseSignalHandler  PSX1_BaseSignalHandler::set_as_handler(const int& signal_code)
{
    struct sigaction res;
    if(sigaction(signal_code,&__glibc_sigaction,&res) != 0)
    {
        throw hh::ErrnoException();
    }
    return PSX1_BaseSignalHandler(res);
}

 PSX1_BaseSignalHandler  get_curent_handler(const int &signal_code)
{
    struct sigaction res;
    if(sigaction(signal_code,NULL,&res) != 0)
    {
        throw hh::ErrnoException();
    }
    return PSX1_BaseSignalHandler(res);
}

INITT_STATIC_OWNER(VirtualSignalHandler);

VirtualSignalHandler::VirtualSignalHandler(const int& flag, const SetSignals &set) :
    PSX1_BaseSignalHandler(get_static_action(), flag, set)
{

}

/*
 BaseSignalHandler VirtualSignalHandler::set_as_handler(const int &signal_code)
{

    auto res = BaseSignalHandler::set_as_handler(signal_code);
    return res;
}
*/


