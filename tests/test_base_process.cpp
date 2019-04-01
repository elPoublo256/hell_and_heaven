#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE run_test_base_process
#include <boost/test/unit_test.hpp>
#include "../core_process/prosess.h"
#include <iostream>


extern char **environ;

BOOST_AUTO_TEST_CASE(test_test)
{

   for(int i = 0; environ[i] != NULL; i++)
   {
       std::cout<<std::string(environ[i])<<std::endl;
   }
    BOOST_CHECK(true);
}

