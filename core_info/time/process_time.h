#pragma once


#include <sys/time.h>
#include <sys/times.h>
#include <time.h>

namespace hh {
namespace core_info {
namespace process_time {
typedef typename clock_t  processer_ticks_t;

class ProcessTime : public tms
{
public:


};


}

}

}