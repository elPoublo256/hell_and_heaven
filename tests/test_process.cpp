#add_executable( run_test_process test_process.cpp)
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test1
#include <boost/test/unit_test.hpp>
#include "../core_process/prosess.h"
#include "../core_files/file_stream.h"
using namespace hh;

int test_pre_main = 0;


BOOST_AUTO_TEST_CASE(test_test)
{

}

BOOST_AUTO_TEST_CASE(two_processe)
{
    class MainProc : public Fork_Process
    {
    public:
        class Proc2 : public Fork_Process
        {
        public:
            int fake_main(const Exe_arg &arg = Exe_arg()) override
            {
              hh::Base_OFile_Stream of("test_two_proc.dat");

              for(int i = 0; i < 5; i++)
              {
                  of << i;
              }
            }
        };
};

}
BOOST_AUTO_TEST_CASE(test_main_process)
{
    auto p = MainProcess::is_Main_Exist();
    BOOST_CHECK_EQUAL(p, false);


    auto ptr = hh::get_main_ptr(); //why undefined reference to get_main_ptr
}
