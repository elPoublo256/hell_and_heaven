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
    write(STDOUT_FILENO,res.get(),len);

}

void test_readwrite_bufer()
{
    std::cout<<__FUNCTION__<<std::endl;
    auto f_name = "wh.txt";
    hh::core_files::Write_FS_File wf(f_name,O_CREAT);
    auto str = "qwerty";
    auto len = strlen(str);
    {
    wf.psx_write((void*)str, strlen(str));
    wf.psx_close();
    }
    hh::core_files::Read_FS_File rf(f_name);
    auto b = std::move(rf.psx_read(std::size_t(len)));
    std::cout<<"buf len = "<<b.size_in_bytes()<<std::endl;
    write(1,b.get(), b.size_in_bytes());
    remove("wh.txt");



}

int main()
{

  //  write(STDOUT_FILENO,res.get(),len);

    //test_readwrite_ptr();
    test_readwrite_bufer();



}

