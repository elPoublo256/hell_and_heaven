#include "psx_signalhandler.h"
#include "../hh_exceptions/hh_exceptions.h"

hh::core_process::BaseSignalHandler::BaseSignalHandler(handler_t handl_function, int flag)
{
    __glibc_sigaction.sa_handler = handl_function;
    __glibc_sigaction.sa_flags = flag;

}
hh::core_process::BaseSignalHandler::BaseSignalHandler(const struct sigaction &glibc_action)
{
    __glibc_sigaction = glibc_action;
}

hh::core_process::BaseSignalHandler::BaseSignalHandler(const BaseSignalHandler &copy)
{
    __glibc_sigaction = copy.__glibc_sigaction;
}

hh::core_process::BaseSignalHandler::BaseSignalHandler(const BaseSignalHandler&& rv_copy)
{
    __glibc_sigaction = std::move(rv_copy.__glibc_sigaction);
}


hh::core_process::BaseSignalHandler::BaseSignalHandler(handler_t handl_function,
                                                       int flag,
                                                       const SetSignals &set)

{
    __glibc_sigaction.sa_handler = handl_function;
    __glibc_sigaction.sa_flags = flag;
    __glibc_sigaction.sa_mask = *(set.get_c_sigset());
}




void hh::core_process::BaseSignalHandler::
set_mask_handler(const hh::core_process::SetSignals &mask) noexcept
{
    __glibc_sigaction.sa_mask = *(mask.get_c_sigset());
}

hh::core_process::BaseSignalHandler hh::core_process::BaseSignalHandler::set_as_handler(const int& signal_code)
{
    struct sigaction res;
    if(sigaction(signal_code,&__glibc_sigaction,&res) != 0)
    {
        throw hh::ErrnoException();
    }
    return BaseSignalHandler(res);
}

hh::core_process::BaseSignalHandler hh::core_process::get_curent_handler(const int &signal_code)
{
    struct sigaction res;
    if(sigaction(signal_code,NULL,&res) != 0)
    {
        throw hh::ErrnoException();
    }
    return BaseSignalHandler(res);
}





