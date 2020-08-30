//#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MODULE test_psx_file
//#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../core_files/psx_files.h"
#include "../hh_exceptions/hh_exceptions.h"
#include <vector>
//BOOST_AUTO_TEST_CASE(test_read_write)

void test_readwrite_ptr()
{
    hh::core_files::Write_FS_File wf("wh.txt");
    auto str = "qwerty";
    auto len = strlen(str);
    {
    wf.psx_write((void*)str, strlen(str));
    wf.psx_close();
    }
    hh::core_files::Read_FS_File rf("wh.txt");
    hh::PSX_Base_Bufer res(len);
    rf.psx_read(res.get_ptr(),len);
    remove("wh.txt");

}

void test_readwrite_bufer()
{
    auto f_name = "wh.txt";
    hh::core_files::Write_FS_File wf(f_name);
    auto str = "qwerty";
    auto len = strlen(str);
    {
    wf.psx_write((void*)str, strlen(str));
    wf.psx_close();
    }
    hh::core_files::Read_FS_File rf(f_name);
    auto b = rf.psx_read(len);



}

int main()
{

  //  write(STDOUT_FILENO,res.get(),len);





}

