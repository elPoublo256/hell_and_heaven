#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_psx_streambud
#include <boost/test/unit_test.hpp>
#include "../core_process/prosess.h"
#include "../core_files/psx_read_streambuf.h"
#include "../core_files/psx_write_streambuf.h"
#include <iostream>

BOOST_AUTO_TEST_CASE(test_create_write_buf)
{
    std::string file1 = "test_create_write_buf_f1";
    std::string file2 = "f2";
    std::shared_ptr<hh::PSX_File> ptr1(new hh::PSX_File(file1, O_WRONLY | O_CREAT, ALL_READ | ALL_WRIGHT));
    hh::PSX_Write_Streambuff<char> buf1(ptr1);
    hh::PSX_Write_Streambuff<char> buf2(file2);
    std::basic_iostream<char> ofst1(&buf1);
    for(int i = 0; i < 10; i++)
    {
        ofst1 << i<<std::endl;
    }

}

