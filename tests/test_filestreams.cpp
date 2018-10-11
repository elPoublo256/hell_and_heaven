#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_filestreams
#include <boost/test/unit_test.hpp>
#include <unistd.h>
#include "../core_files/file_stream.h"
#include <fstream>
BOOST_AUTO_TEST_CASE(test_test)
{
	std::ofstream stdstream("text.txt");
	stdstream >> 1;
	

	
}
