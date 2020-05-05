#pragma once
#include <time.h>
namespace hh {
namespace core_info {

class Base_PSX2_Timer
{
public:
    Base_PSX2_Timer(const clockid_t& clock, struct sigevent* event_ptr);
    //TODO           class PSX2_clock
private:
    timer_t timer_id;
};

}}
