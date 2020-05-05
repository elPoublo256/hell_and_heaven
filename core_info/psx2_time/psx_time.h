#pragma once
#include <time.h>
namespace hh {
namespace core_info {




class PSX2_time : public timespec
{
public:
    PSX2_time(){}
    PSX2_time(const clockid_t &clock_id = CLOCK_REALTIME);
    inline auto get_seconds(){return this->tv_sec;}
    inline auto get_nanoseconds(){return this->tv_nsec;}
};

//TODO clocks , settime balbalbal

}

}
