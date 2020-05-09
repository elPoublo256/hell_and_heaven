#pragma once
#include <pthread.h>
#include "../hh_exceptions/hh_exceptions.h"
#include "../core_process/static_hanler.h"
namespace hh {
namespace threads {

/*class PSX_Thread_Error : public std::runtime_error
{
public:
    PSX_Thread_Error(){}
    PSX_Thread_Error(const std::string& err) : std::runtime_error(s){}
};*/

class PSX_Thread_Errno_Error : /*public PSX_Thread_Error,*/ public hh::ErrnoException
{

};

/*!
 * \brief The PSX_Thread class
 * This class provide POSIX-Thread
 */

class PSX_Thread
{
  public:
    PSX_Thread() noexcept;
    void run();

    //PSX_Thread()
protected:
     void *(*__function) (void *);
     pthread_t c_thread;



};



}

}
