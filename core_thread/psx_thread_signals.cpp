#include "psx_thread_signals.h"
using namespace hh::threads;

void send_signal(const PSX_Thread &pthread, int signal)
{
    if(pthread_kill(pthread.get_c_thread(), signal) != 0)
    {
        throw PSX_Thread_Errno_Error();
    }


}
