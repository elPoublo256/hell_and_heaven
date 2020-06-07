#pragma once
#include <pthread.h>
#include <time.h>
#include "../hh_exceptions/hh_exceptions.h"
namespace hh {
namespace threads {


class PSX_Mutex_Errno_Error : /*public PSX_Thread_Error,*/ public hh::ErrnoException
{
 public:
    PSX_Mutex_Errno_Error() : hh::ErrnoException() {}
};

/*!
 * \brief The PSX_Mutex class
 * Class of realisation dinamic PTHREAD-mutex
 */
class PSX_Mutex
{
    PSX_Mutex();
    PSX_Mutex(pthread_mutexattr_t* atr_ptr);
    ~PSX_Mutex();
    void lock();
    void unlock();
    void try_lock();
    void timed_lock(const timespec& c_time);

private:
    pthread_mutex_t* __mut;
    pthread_mutexattr_t* __atr = NULL;
};
}
}
