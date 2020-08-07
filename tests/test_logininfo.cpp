#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_logininfo
#include <boost/test/unit_test.hpp>
#include "../core_user/psx_login.h"
#include <iostream>

BOOST_AUTO_TEST_CASE(test_test)
{
    struct utmpx origin;
    origin.ut_pid = 666;
    origin.ut_session = 888;
    std::string host = "127.0.0.1";
    for(int i = 0; i <host.length();i++){origin.ut_host[i] = host[i];}
    origin.ut_host[host.length()] = char(NULL);
    hh::core_user::PSX_Login_Info info(&origin);
    BOOST_CHECK_EQUAL(host, info.get_host());
    BOOST_CHECK_EQUAL(666, info.get_pid());

}

