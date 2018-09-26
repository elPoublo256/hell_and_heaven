#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test1
#include <boost/test/unit_test.hpp>
#include "../core_process/prosess.h"
BOOST_AUTO_TEST_CASE(test_test)
{
	auto p =  processes::ProcessFubric::rvCreateProcess();
	auto pid1 = p.get_pid();

}
