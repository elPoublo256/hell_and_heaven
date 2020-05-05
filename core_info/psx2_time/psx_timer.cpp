#include "psx_timer.h"
#include "../../hh_exceptions/hh_exceptions.h"
using namespace hh::core_info;

Base_PSX2_Timer::Base_PSX2_Timer(const clockid_t &clock, sigevent *event_ptr)
{
    if(timer_create(clock, event_ptr,&timer_id) != 0)
    {
            throw hh::ErrnoException();
    }
}
