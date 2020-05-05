#include "psx_time.h"
#include "../../hh_exceptions/hh_exceptions.h"
using namespace hh::core_info;

PSX2_time::PSX2_time(const clockid_t &clock_id)
{
    if(clock_gettime(clock_id, this) != 0)
    {
        throw hh::ErrnoException();
    }
}
