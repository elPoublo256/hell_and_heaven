#pragma once
#include "static_hanler.h"
#include "../hh_exceptions/hh_exceptions.h"
namespace hh {
namespace process {
class Error_Set_Handler : public hh::ErrnoException
{
public:
    Error_Set_Handler() : hh::ErrnoException() {}

};

struct Base_Exit_Handler
{
    virtual void apply() = 0;
};

/*!
 * \brief The SUSV3_Base_Exit_Process_Handler class is the Base class for all handler exit process
 * set handler using "int atexit()"
 */
class SUSV3_Base_Exit_Process_Handler : public Base_Exit_Handler
{
public:
    SUSV3_Base_Exit_Process_Handler();
    /*!
     * \brief Base_Exit_Process_Handler
     * construct Base_Exit_Process_Handler from pounter to function void f(void)
     */
    SUSV3_Base_Exit_Process_Handler(void (*handler)(void)) noexcept;
    /*!
     * \brief apply
     * set as
     */
    virtual void apply() final override;

protected:
    /*!
     *htis is pointer to function, wich will be emited before the process will exit
     */
    void (*__handler)(void);

    /*!
     * \brief set_handler
     */
    void set_handler(void (*handler)(void)){this->__handler = handler;}

};
//TODO add ifdef
/*!
 * \brief The GLIBC_Base_Exit_Process_Handler class set exit handler using "int on_exit()"
 */
class GLIBC_Base_Exit_Process_Handler : public Base_Exit_Handler
{

};

#define PUBLIC_VIRTUAL_SIGNAL_HANDLER(CLASS)  public hh::smart_functor::Smart_Functor<CLASS, void, void>

class Virtual_SUSV3_Exit_Process_Handler :
  public hh::smart_functor::NOARGS_Smart_Functor<Virtual_SUSV3_Exit_Process_Handler>
, public SUSV3_Base_Exit_Process_Handler{
public:
    Virtual_SUSV3_Exit_Process_Handler();

    virtual void action() = 0;

};


class Lambda__Exit_Process_Handler
{
    //TODO constructor from lambda

};




}
}
