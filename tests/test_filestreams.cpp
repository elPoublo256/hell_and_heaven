#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_filestreams
#include <boost/test/unit_test.hpp>
#include <unistd.h>
#include "../core_files/file_stream.h"
#include <list>
using namespace hh;
void test_base_filestream()
{
    std::string filename("checkbasefilestream");
    std::list<int> l1, l2;
    Base_OFile_Stream ofsrt(filename);
    for(int i = 0; i < 10; i++)
    {
        auto r = rand();
        l1.push_back(r);
        ofsrt << r;

    }
    Base_IFile_Stream ifsrt(filename);
    for(int i = 0; i < 10; i++)
    {
        int r;
        ifsrt >> r;
        l2.push_back(r);
    }
    BOOST_CHECK_EQUAL_COLLECTIONS(l1.begin(), l1.end(), l2.begin(), l2.end());

}
BOOST_AUTO_TEST_CASE(test_test)
{
    test_base_filestream();
}

BOOST_AUTO_TEST_CASE(test_OpenError)
{



    std::string should_be_what("A signal was caught during open().");
    try
    {

          throw OpenFileError(EINTR);
    }
    catch(OpenFileError &err)
    {
      BOOST_CHECK_EQUAL(err.err_what, should_be_what);
    }

}

BOOST_AUTO_TEST_CASE(test_BaseIO_from_fd)
{
    hh::Base_OFile_Stream out(STDOUT_FILENO);
    out << "HELOW";
}

BOOST_AUTO_TEST_CASE(test_BaseIO_shared_ptr)
{
    std::shared_ptr<PSX_File> out_ptr =
            std::shared_ptr<Base_OFile_Stream>(
                (new Base_OFile_Stream(STDOUT_FILENO)));
    out_ptr << "HELLOW FROM PTR" <<'\n' << "DOUBLE_LINE";
    out_ptr << "QQQQQ";
}


