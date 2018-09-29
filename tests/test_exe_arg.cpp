#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_exe_arg
#include <boost/test/unit_test.hpp>
#include "../core_process/prosess.h"
#include <string>
#include <string.h>
#include <iostream>
using processes::Exe_arg;
BOOST_AUTO_TEST_CASE(test_test)
{
	BOOST_CHECK(true);

	Exe_arg arg(2,std::string("a"), std::string("b"));
	BOOST_CHECK_EQUAL(arg.argc(), 3);
	BOOST_CHECK_EQUAL(arg.argv_[0], std::string("a"));	
	BOOST_CHECK_EQUAL(arg.argv_[1], std::string("b"));
    char** c_string = arg.cstr_argv();
    BOOST_CHECK_EQUAL(strcmp(c_string[0], "a"), 0);
    BOOST_CHECK_EQUAL(strcmp(c_string[1], "b"), 0);
	BOOST_CHECK(c_string[2] == NULL);
}
