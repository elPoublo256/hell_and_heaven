#pragma once
#include <pthread.h>
#include "../hh_exceptions/hh_exceptions.h"
#include "../core_process/static_hanler.h"
#include <functional>
#include <tuple>
namespace hh {
namespace threads {

class PSX_Thread_Error : public std::runtime_error
{
public:

    PSX_Thread_Error(const std::string& err) : std::runtime_error(err){}
};

class PSX_Thread_Errno_Error : /*public PSX_Thread_Error,*/ public hh::ErrnoException
{
 public:
    PSX_Thread_Errno_Error() : hh::ErrnoException() {}
};

/*!
 * \brief The Base_PSX_Thread class
 * This class provide POSIX-Thread
 */

class Base_PSX_Thread
{
  public:
    std::function<void*(void*)> __function;
    Base_PSX_Thread();

    /*!
     * \brief Base_PSX_Thread
     * create Base_PSX_Thread with defualt atributs
     */
    Base_PSX_Thread(std::function<void*(void*)> function);

    /*!
     * \brief Base_PSX_Thread
     * \param atr - seted atributs
     */
    //Base_PSX_Thread( pthread_attr_t* atr, void*(*function)(void *));
    virtual ~Base_PSX_Thread();//TODO
    /*!
     * \brief run
     * create PThread with base-function
     * \param arg - argument in pointer
     * \throw PSX_Thread_Errno_Error
     */
    void run(void* arg);

    void join(void* res);
    void join_no_res();

    /*!
     * \brief detech - detech thread
     */
    void detech();
    void cancle();
    bool operator == (const Base_PSX_Thread& other);
    bool inline operator != (const Base_PSX_Thread& other) {return !((*this)==other);}

#ifdef __USE_GNU
//TODO
//extern int pthread_tryjoin_np (pthread_t __th, void **__thread_return) __THROW;
//extern int pthread_timedjoin_np (pthread_t __th, void **__thread_return,
//				 const struct timespec *__abstime);
#endif

static void* __f_for_t(void* arg)
{
    auto ptr_thread = (Base_PSX_Thread*) arg;

   ptr_thread->__res = ptr_thread->__function(arg);
    return NULL;}


protected:


     pthread_t* _c_thread;
     pthread_attr_t* _c_atr;
     void* __arg;
     void* __res;



};
//TODO if Res is r-value




template <class Res, class ...Args>
class PSX_Thread// : public Base_PSX_Thread
{
public:

    typedef std::function<Res(Args...)> functor;
    void run(Args... args)
    {
        __call_f = std::bind(_functor,args...);
        Base_PSX_Thread t(PSX_Thread::_main_function);
        t.run(this);
        t.join_no_res();
        //Base_PSX_Thread::run(this);
        //this->_main_function(this);
    }
    PSX_Thread(auto func)// : Base_PSX_Thread(PSX_Thread<Res,Args...>::_main_function)
    {_functor = func;}

    ~PSX_Thread()
    {
    }

protected:
    std::function<Res()> __call_f;
    functor _functor;
    Res _obj_res;

public:
    static void* _main_function(void* arg)
    {
       PSX_Thread<Res,Args...>* ptr_thread = (PSX_Thread<Res,Args...>*)arg;
       ptr_thread->_obj_res = ptr_thread->__call_f();
       return NULL;



    }



};



}

}
