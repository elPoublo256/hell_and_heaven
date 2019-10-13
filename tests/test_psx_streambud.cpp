//#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MODULE test_psx_streambud
//#include <boost/test/unit_test.hpp>
//#include "../core_process/prosess.h"
//#include "../core_files/psx_read_streambuf.h"
//#include "../core_files/psx_write_streambuf.h"
//#include <iostream>

///*
//BOOST_AUTO_TEST_CASE(test_write_buf)
//{
//    std::string file1 = "test_create_write_buf_f1.txt";
//    std::string file2 = "test_create_write_buf_f2.txt";
//    std::shared_ptr<hh::PSX_File> ptr1(new hh::PSX_File(file1, O_WRONLY | O_CREAT, ALL_READ | ALL_WRIGHT));
//    hh::PSX_Write_Streambuff<char> buf1(ptr1);
//    hh::PSX_Write_Streambuff<char> buf2(file2);
//    std::basic_iostream<char> ofst1(&buf1);
//    std::basic_iostream<char> ofst2(&buf2);
//    for(int i = 0; i < 10; i++)
//    {
//       // ofst2 << i<<std::endl;
//        ofst1 << i;
//    }


//}
//*/
//BOOST_AUTO_TEST_CASE(test_read_buf)
//{
//    std::string file_name("test_read_psx_streambuf.txt");
//    std::ofstream stl_f(file_name);
//    for(int i = 0; i < 10; i++)
//    {
//        stl_f << i;
//    }
//    stl_f.close();
//    hh::PSX_Read_Streambuff<char> pw(file_name);
//    std::basic_iostream<char> psx_f(&pw);
//    for(int i = 0; i < 10; i++)
//    {
//        int res = 666;
//        psx_f >> res;
//        std::cout << "get res "<<res<<std::endl;
//    }

//}

