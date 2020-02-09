#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_setsignals
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../core_process/psx_signals.h"

BOOST_AUTO_TEST_CASE(test_glibc)
{
    sigset_t s;
    sigemptyset(&s);
    BOOST_CHECK_EQUAL(sigismember(&s, SIGINT), 0);
    sigaddset(&s, SIGINT);
    BOOST_CHECK_EQUAL(sigismember(&s, SIGINT), 1);
}


BOOST_AUTO_TEST_CASE(test_createing_sets)
{
    hh::core_process::SetSignals s1{SIGBUS,SIGILL,SIGINT};
    BOOST_CHECK(s1.is_member(SIGBUS));
    BOOST_CHECK(s1.is_member(SIGILL));
    BOOST_CHECK(s1.is_member(SIGINT));
    hh::core_process::set_signal_mask(s1);
    auto s2 = hh::core_process::get_qurent_mask();
    BOOST_CHECK(s2.is_member(SIGBUS));
    BOOST_CHECK(s2.is_member(SIGILL));
    BOOST_CHECK(s2.is_member(SIGINT));

    hh::core_process::send_signal_to_self(SIGBUS);
    hh::core_process::send_signal_to_self(SIGILL);
    hh::core_process::send_signal_to_self(SIGINT);

    auto s_wait = hh::core_process::get_whaiting_signals();
    BOOST_CHECK(s_wait.is_member(SIGBUS));
    BOOST_CHECK(s_wait.is_member(SIGILL));
    BOOST_CHECK(s_wait.is_member(SIGINT));




}

