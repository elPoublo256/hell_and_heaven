#include "../core_process/psx_setsignals.h"
#include "../core_process/psx_signalhandler.h"
#include "../core_process/psx2_signal_info.h"
#include <iostream>
// you can use only one one time this overload VirtualSignalHandler
class TestVHandler : public hh::core_process::VirtualSignalHandler
{
public:
    std::string ss = "it is wark";
    void action(int s) override
    {
        std::cout << ss << std::endl;
    }

    TestVHandler() : VirtualSignalHandler(0){}
};

//if you need in two ore more Virtual Handlers, use this macro
class Test2 : PUBLIC_VIRTUAL_SIGNAL_HANDLER(Test2)
{
    public:
    Test2() : PSX1_BaseSignalHandler(Smart_Functor::get_static_action(),0,hh::core_process::SetSignals()) {}
    void action(int s) override {std::cout << "Test2 is wark"<<std::endl;}
};




class InfoHandler : public hh::core_process::InfoVirtualSignalHandler
{
public:
    virtual void info_action(int signal,
                        const hh::core_process::SignalInfo& info,
                        const hh::core_process::UserContext& context)
    {
        std::cout << "InfoHandler is wark"<<std::endl;
    }
    InfoHandler(const int& s = 0) : hh::core_process::InfoVirtualSignalHandler(s, hh::core_process::SetSignals(SA_SIGINFO)){}
};

void test_handler_psx1()
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

void test_handler_psx2()
{

  /*  hh::core_process::BaseSignalHandler ih(
                [](int s, siginfo_t* inf, void* con)
    {std::cout << "InfoHandler is wark"<<std::endl;},
    0, hh::core_process::SetSignals());
*/
    InfoHandler ih;
    auto before = ih.set_as_handler(SIGINT);
    hh::core_process::send_signal_to_self(SIGINT);

}


//and this macro
INITT_STATIC_OWNER(Test2);

int main()
{
    test_handler_psx1();

    test_handler_psx2();

    return 0;
}
