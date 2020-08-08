#include "psx_mutex.h"
#include "psx_thread.h"
using namespace hh::threads;
PSX_Mutex::PSX_Mutex()
{
    auto res = pthread_mutex_init(__mut,__atr);
    if(res)
    {
        throw PSX_Mutex_Errno_Error();
    }
}

PSX_Mutex::PSX_Mutex(pthread_mutexattr_t *atr_ptr)
{
    __atr = atr_ptr;
    auto res = pthread_mutex_init(__mut,__atr);
    if(res)
    {
        throw PSX_Mutex_Errno_Error();
    }
}

PSX_Mutex::~PSX_Mutex()
{
    if(__atr){
    auto res = pthread_mutexattr_destroy(__atr);
    if(res){ throw "ERROR DESTROY PTHREAD_MUTEX";}
    }
}

void PSX_Mutex::lock()
{
    auto res = pthread_mutex_lock(__mut);
    if(res)
    {
        throw PSX_Mutex_Errno_Error();
    }

}

void PSX_Mutex::unlock()
{
    auto res = pthread_mutex_unlock(__mut);
    if(res)
    {
        throw PSX_Mutex_Errno_Error();
    }
}

void PSX_Mutex::try_lock()
{
    auto res = pthread_mutex_trylock(__mut);
    if(res)
    {
        throw PSX_Mutex_Errno_Error();
    }
}


void PSX_Mutex::timed_lock(const timespec &c_time)
{
    auto res = pthread_mutex_timedlock(__mut, &c_time);
    if(res)
    {
        throw PSX_Mutex_Errno_Error();
    }
}
