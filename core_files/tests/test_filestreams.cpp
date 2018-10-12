#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE test_filestreams
#include <boost/test/unit_test.hpp>
#include <unistd.h>
#include "../file_stream.h"
#include <fstream>
#include <iostream>



void read_to_list(std::list<int> &l, std::list<int> &l2)
{
    auto fd = open("check.txt", O_WRONLY | O_CREAT);
    for(int i = 0; i < 100; i++)
    {
        l.push_back(i);
       write(fd, &i, sizeof(int));
    }
    Base_IFile_Stream ifile_rval_string(std::string("check.txt"));

    for(int i = 0; i < 100; i++)
    {
        int t;
        ifile_rval_string >> t;
        l2.push_back(t);

    }

}

void read_base_ifstream()
{

    std::list<int> l, l2;
    read_to_list(l, l2);
    BOOST_CHECK_EQUAL_COLLECTIONS(l.begin(), l.end(), l2.begin(), l2.end() );

}


void write_base_ifstream()
{
  std::list<int> l1, l2;
  Base_OFile_Stream off(std::string("check2.txt"));
  for(int i = 0; i < 10; i++)
  {
      l1.push_back(i);

      off << i;

  }

 //close(off.filedcripter());

  Base_IFile_Stream iff(off.filedcripter());

  std::cout<<"ERRNO = " << errno << std::endl;
  for(int i = 0; i < 10; i++)
  {
      std::cout << "fd = "<<iff.filedcripter()<<std::endl;
      int t;
      iff >> t;
      l2.push_back(t);

  }
  BOOST_CHECK_EQUAL_COLLECTIONS(l1.begin(), l1.end(), l2.begin(), l2.end() );

}


BOOST_AUTO_TEST_CASE(test_test)
{
    //read_base_ifstream();
    write_base_ifstream();
   }
