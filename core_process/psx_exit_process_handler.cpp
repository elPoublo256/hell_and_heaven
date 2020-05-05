#include "psx_exit_process_handler.h"
#include "stdlib.h"
using namespace hh::process;
SUSV3_Base_Exit_Process_Handler::SUSV3_Base_Exit_Process_Handler()
{
    this->__handler = nullptr;
}

SUSV3_Base_Exit_Process_Handler::SUSV3_Base_Exit_Process_Handler(void (*handler)()) noexcept
{
    this->__handler = handler;
}

void SUSV3_Base_Exit_Process_Handler::apply()
{
    auto res = atexit(__handler);
    if(res != 0)
    {
        throw Error_Set_Handler();
    }

}

INITT_STATIC_OWNER(Virtual_SUSV3_Exit_Process_Handler);
Virtual_SUSV3_Exit_Process_Handler::Virtual_SUSV3_Exit_Process_Handler()
{
    set_owner(this);
    //this->set_handler(this->StatFunct::action);
    __handler = get_static_action();
    }


