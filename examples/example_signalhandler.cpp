#include "../core_process/psx_setsignals.h"
#include "../core_process/psx_signalhandler.h"
#include <iostream>

class TestVHandler : public hh::core_process::VirtualSignalHandler
{
public:
    void action(int s) override
    {
        std::cout << "it is wark";
    }

    TestVHandler() : VirtualSignalHandler(0){}
};

int main()
{
  TestVHandler h;
 auto before_handler =  h.set_as_handler(SIGCONT);
 hh::core_process::send_signal_to_self(SIGCONT);

 before_handler.set_as_handler(SIGCONT);


}
