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
    hh::PSX_File write_file(filename,  O_WRONLY | O_RDONLY | O_CREAT, ALL_READ);
    write_file.psx_write(vec.data(), vec.size() * sizeof(int));
    }
    catch(hh::ErrnoException& err)
    {
        std::cout <<"cach errno" << err.what()<<std::endl;
    }

    try{
     hh::PSX_File rf(filename, O_RDONLY, S_IRUSR | S_IRGRP | S_IROTH );
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

