#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_exearg
#include <boost/test/unit_test.hpp>
#include "../core_process/prosess.h"
#include <iostream>

BOOST_AUTO_TEST_CASE(test_test)
{
    using namespace hh;


    Exe_arg ar1;

    Exe_arg ar2(3,
                std::string("a"),
                std::string("b"),
                std::string("c"));

    std::vector<std::string> ar2_str;
    ar2_str.push_back(std::string("a"));
    ar2_str.push_back(std::string("b"));
    ar2_str.push_back(std::string("c"));


    BOOST_CHECK_EQUAL_COLLECTIONS(
                ar2.argv_.begin(),
                ar2.argv_.end(),
                ar2_str.begin(),
                ar2_str.end());
\
    BOOST_CHECK_EQUAL(ar2.argc(), 4);

    BOOST_CHECK(true);
}

