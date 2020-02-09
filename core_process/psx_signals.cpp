#include "psx_signals.h"
#include "../hh_exceptions/hh_exceptions.h"

void hh::core_process::send_signal(const int &signal_code, const pid_t &pid)
{
    if(kill(pid, signal_code) != 0)
    {
        throw hh::ErrnoException();
    }
}

void hh::core_process::send_signal_to_group(const int &signal_code, pid_t &pidgrup)
{
    if(killpg(pidgrup, signal_code) != 0)
    {
        throw hh::ErrnoException();
    }
}


void hh::core_process::send_signal_to_self(const int &signal)
{
    if(raise(signal) != 0)
    {
        throw hh::ErrnoException();
    }
}

void hh::core_process::SetSignals::set_empty()
{
    if(sigemptyset(&__glibc_sigset_prt) != 0)
    {
         throw hh::ErrnoException();
    }

}


void hh::core_process::SetSignals::add_signal(const int &signal_code)
{
    if(sigaddset(&__glibc_sigset_prt, signal_code) != 0)
    {
        throw hh::ErrnoException();
    }
}

void hh::core_process::SetSignals::delete_signal(const int &signalecode)
{
    if(sigdelset(&__glibc_sigset_prt, signalecode) != 0)
    {
        throw ErrnoException();
    }
}

hh::core_process::SetSignals::SetSignals()
{
    this->set_empty();
}

hh::core_process::SetSignals::SetSignals(const int &signal)
{
    this->set_empty();
    add_signal(signal);
}

hh::core_process::SetSignals::SetSignals(const std::initializer_list<int> &inilist)
{
    set_empty();
    for(int sig : inilist)
    {
        add_signal(sig);
    }
}

hh::core_process::SetSignals::SetSignals(const sigset_t& c_sigset_prt)
{
    __glibc_sigset_prt = c_sigset_prt;

}

hh::core_process::SetSignals::SetSignals(const SetSignals &copy)
{
    __glibc_sigset_prt = copy.__glibc_sigset_prt;
}

const sigset_t* hh::core_process::SetSignals::get_c_sigset() const
{
    return &__glibc_sigset_prt;
}

hh::core_process::SetSignals::SetSignals(SetSignals &&rv_copy)
{
    __glibc_sigset_prt = std::move(rv_copy.__glibc_sigset_prt);
}

bool hh::core_process::SetSignals::is_member(const int &signal) const noexcept
{
    if(sigismember(&__glibc_sigset_prt, signal) == 1)
    {
        return true;
    }

    return false;
}

hh::core_process::SetSignals
hh::core_process::set_signal_mask(const int &how,
                                   const SetSignals &set)
{
   sigset_t res_ptr;
   if(sigprocmask(how, set.get_c_sigset(),&res_ptr) != 0)
   {
       throw hh::ErrnoException();
   }
   return SetSignals(res_ptr);
}


hh::core_process::SetSignals&&
hh::core_process::get_qurent_mask()
{
    sigset_t res_ptr;
    if(sigprocmask(SIG_SETMASK,NULL,&res_ptr) != 0)
    {
        throw hh::ErrnoException();
    }
    return std::move(SetSignals(res_ptr));
}

hh::core_process::SetSignals&&
hh::core_process::get_whaiting_signals()
{
    sigset_t s;
    sigpending(&s);
    return std::move(SetSignals(s));

}








