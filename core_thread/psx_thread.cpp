#include "psx_thread.h"
using namespace hh::threads;


Base_PSX_Thread::Base_PSX_Thread()
{
    _c_thread = NULL;
    auto res = pthread_attr_init(_c_atr);
    if(res != 0)
    {
        throw PSX_Thread_Errno_Error();
    }

}

Base_PSX_Thread::Base_PSX_Thread(std::function<void *(void *)> function)
{
    _c_thread = NULL;
    __function = function;
}
/*
Base_PSX_Thread::Base_PSX_Thread(pthread_attr_t *atr, void *(*function)(void *))
{
    _c_thread = NULL;
    __function = function;
    _c_atr = atr;
}
*/
Base_PSX_Thread::~Base_PSX_Thread()
{
    if(_c_thread != NULL)
    {
        pthread_cancel(*_c_thread);
        delete _c_thread;
    }
}


void Base_PSX_Thread::run(void *arg)
{
    __arg = arg;
    _c_thread = new pthread_t();
    int res = pthread_create(_c_thread,_c_atr , Base_PSX_Thread::__f_for_t, this);
    if(res != 0)
    {
        throw PSX_Thread_Errno_Error();
    }
}

bool Base_PSX_Thread::operator ==(const Base_PSX_Thread& other)
{
    if(_c_thread == NULL || other._c_thread == NULL)
    {
        return false;
    }

    auto res = pthread_equal(*_c_thread, *(other._c_thread));
    return res  != 0;
}

void Base_PSX_Thread::join(void *res)
{
  if(_c_thread == NULL)
  {
      throw PSX_Thread_Error("thread is not runned");
  }
  auto ress = pthread_join(*_c_thread,
               &res);
  res = this->__res;
  if(ress != 0)
  {
      throw PSX_Thread_Errno_Error();
  }
  _c_thread = NULL;
}

void Base_PSX_Thread::join_no_res()
{
    void* res;
    if(_c_thread == NULL)
    {
        throw PSX_Thread_Error("thread is not runned");
    }
    auto ress = pthread_join(*_c_thread,
                 &res);
    res = __res;
    if(ress != 0)
    {
        throw PSX_Thread_Errno_Error();
    }
    _c_thread = NULL;

}

void Base_PSX_Thread::cancle()
{
    auto res = pthread_cancel(*_c_thread);
    if(res != 0)
    {
        throw PSX_Thread_Errno_Error();
    }
}

void Base_PSX_Thread:: detech()
{
    if(_c_thread == NULL)
    {
        throw PSX_Thread_Error("thread is not runned");
    }

    auto res = pthread_detach(*_c_thread);
    if(res != 0)
    {
        throw PSX_Thread_Error("thread is not runned");
    }
    _c_thread = NULL;
}


