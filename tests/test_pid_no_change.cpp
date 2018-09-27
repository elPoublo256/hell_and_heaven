#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_pid_no_change
#include <boost/test/unit_test.hpp>
#include <unistd.h>
BOOST_AUTO_TEST_CASE(test_test)
{
 auto cur_pid = getpid();
 for(int i = 0; i < 100; i++)
 {
	 BOOST_CHECK_EQUAL(cur_pid, getpid());
 } 
}
