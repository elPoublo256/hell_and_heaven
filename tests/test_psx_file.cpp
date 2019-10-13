#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_psx_file
#include <boost/test/unit_test.hpp>
#include <iostream>
#include "../core_files/psx_files.h"
#include "../hh_exceptions/hh_exceptions.h"
#include <vector>
BOOST_AUTO_TEST_CASE(test_read_write)
{

    std::string filename = "at";
    std::vector<int> vec {1,2,3,4,5,6,7,8,10,134};
    auto size_buff = vec.size();
    errno = 0;
     try
    {
    hh::psx_file::PSX_File write_file(filename,  O_WRONLY | O_RDONLY | O_CREAT, ALL_READ);
    write_file.psx_write(vec.data(), vec.size() * sizeof(int));
    }
    catch(hh::ErrnoException& err)
    {
        std::cout <<"cach errno" << err.what()<<std::endl;
    }

    try{
     hh::psx_file::PSX_File rf(filename, O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH );
     std::vector<int> filebuf(size_buff);
     rf.psx_read(filebuf.data(), filebuf.size() * sizeof(int));
     BOOST_CHECK_EQUAL_COLLECTIONS(filebuf.begin(), filebuf.end(), vec.begin(), vec.end());
    }
    catch(hh::ErrnoException& err)
    {
        std::cout <<"cach errno" << err.what()<<std::endl;
    }
    remove(filename.c_str());
    BOOST_CHECK_EQUAL(errno, 0);

}

BOOST_AUTO_TEST_CASE(test_lseeck)
{
    errno = 0;
 std::string filename = "test_lseeck";
 hh::psx_file::PSX_File fl(filename,  O_RDWR | O_CREAT, ALL_READ | ALL_WRIGHT);
 std::vector<int> vec{0,1,2,3,4,5,6,7,8,9};
 BOOST_CHECK_EQUAL(vec.size(), 10);
 fl.psx_write(vec.data(),vec.size() * sizeof(int));
 int res_red;

 for(int i = 0; i < 100; i++)
 {
     int pos = rand() % 10;
     try
     {
     fl.lseek_from_begin(pos * sizeof(int));
     fl.psx_read(&res_red, sizeof(int));
     }
     catch(hh::ErrnoException& err)
     {
         std::cerr<<err.what()<<" "<<errno<<std::endl;
     }

     BOOST_CHECK_EQUAL(res_red, vec[pos]);
 }
fl.psx_close();
remove(filename.c_str());
BOOST_CHECK_EQUAL(errno, 0);
}

