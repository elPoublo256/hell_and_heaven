#include "../core_process/psx_setsignals.h"
#include "../core_process/psx_signalhandler.h"
#include <iostream>
// you can use only one one time this overload VirtualSignalHandler
class TestVHandler : public hh::core_process::VirtualSignalHandler
{
public:
    std::string ss = "it is wark";
    void action(int s) override
    {
        std::cout << ss;
    }

    TestVHandler() : VirtualSignalHandler(0){}
};

//if you need in two ore more Virtual Handlers, use this macro
class Test2 : PUBLIC_VIRTUAL_SIGNAL_HANDLER(Test2)
{
    public:
    Test2() : BaseSignalHandler(Smart_Functor::get_static_action(),0,hh::core_process::SetSignals()) {}
    void action(int s) override {std::cout << "Test2 is wark"<<std::endl;}
};

//and this macro
INITT_STATIC_OWNER(Test2);

int main()
{

  TestVHandler h;
  Test2 h2;
 auto before_handler =  h.set_as_handler(SIGCONT);
 hh::core_process::send_signal_to_self(SIGCONT);
 auto before_handler_2 = h2.set_as_handler(SIGCONT);
 hh::core_process::send_signal_to_self(SIGCONT);
 before_handler_2.set_as_handler(SIGCONT);
 hh::core_process::send_signal_to_self(SIGCONT);

}
