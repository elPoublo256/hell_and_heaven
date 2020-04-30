#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_signal_handler
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../core_process/psx_signals.h"
#include "../core_process/psx_signalhandler.h"
#include "../core_process/psx2_signal_info.h"
#include <type_traits>

using namespace hh::core_process;
int last_sig = 0;

pid_t pid_send = 0;
void handler(int sig)
{
    last_sig =sig;
}







BOOST_AUTO_TEST_CASE(test_BaseSignalHandler)
{
    hh::core_process::PSX1_BaseSignalHandler h(handler, 0, hh::core_process::SetSignals());
    h.set_as_handler(SIGINT);
    hh::core_process::send_signal_to_self(SIGINT);
    BOOST_CHECK_EQUAL(last_sig, SIGINT);

}

BOOST_AUTO_TEST_CASE(testInfoHandler)
{

}







