#include "../core_process/psx_exit_process_handler.h"
#include <iostream>
class TestHandlerExit : public hh::process::Virtual_SUSV3_Exit_Process_Handler
{
public:
    virtual void action() override
    {
        std::cout << "HANDLER EXIT"<< std::endl;
    }
};

int main()
{
    TestHandlerExit t;
    t.apply();
    exit(0);
}
