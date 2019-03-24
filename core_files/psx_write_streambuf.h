#pragma once
#include "psx_files.h"
#include <streambuf>
#include <memory>
#include <fstream>
#include <cstring>
#include <iostream>


namespace hh {


template <class CharT,
          class Traits = std::char_traits<CharT>,
          class Allocator = std::allocator<CharT>
          >
class PSX_Write_Streambuff : public std::basic_streambuf<CharT, Traits>
{
public:
    typedef CharT                               char_type;
    typedef Traits                              traits_type;
    typedef typename traits_type::int_type 		int_type;
    typedef typename traits_type::pos_type 		pos_type;
    typedef typename traits_type::off_type 		off_type;
    using Base = std::basic_streambuf<CharT, Traits>;
   PSX_Write_Streambuff(std::shared_ptr<hh::PSX_File> file_ptr, std::size_t size_buf = DEFULT_BUF_SIZE):
       __psx_file_ptr(file_ptr)
   {
       __bufer.resize(size_buf);
       Base::setp(__bufer.data(), __bufer.data() + __bufer.size());
       this->_M_out_cur = __bufer.data();
   }

   PSX_Write_Streambuff(std::string file_name,
                        permiss_t permis = ALL_READ | ALL_WRIGHT,
                        std::size_t size_buf = 3) :
   __psx_file_ptr(new PSX_File(file_name, O_WRONLY | O_CREAT, permis))
   {
       __bufer.resize(size_buf);
       Base::setp(__bufer.data(), __bufer.data() + __bufer.size());
       this->_M_out_cur = __bufer.data();
   }
   ~PSX_Write_Streambuff()
   {

       this->sync();
   }


protected:
    std::shared_ptr<hh::PSX_File> __psx_file_ptr;
    std::vector<CharT, Allocator> __bufer;



    const PSX_Write_Streambuff& operator = (const PSX_Write_Streambuff& other)
    {
        return *this;
    }



    virtual int_type overflow(int_type __c = Traits::eof())
    {
        errno = 0;
        std::cout << __FUNCTION__<<" "<<__c<<std::endl;
        for(auto a : __bufer)
        {
            std::cout << "pint:"<<a<<std::endl;
        }

        __psx_file_ptr->psx_write(__bufer.data(), __bufer.size() * sizeof(CharT));
        __bufer.resize(__bufer.size());
        this->setp(__bufer.data(), __bufer.data() + __bufer.size() );
        std::cout <<"errno = "<< errno <<std::endl;
        return __c;



    }


virtual int sync()
    {
        std::cout<<std::endl;
        std::cout<<__FUNCTION__<<std::endl;
        errno = 0;
        __psx_file_ptr->psx_write(__bufer.data(), std::distance(__bufer.data(), this->_M_out_cur) * sizeof(CharT));

        __bufer.resize(__bufer.size());
        this->setp(__bufer.data(), __bufer.data() + __bufer.size());


        return 0;
    }
virtual int pubsync()
    {
        std::cout << __FUNCTION__<<std::endl;
        return this ->sync();
    }
};







template <class CharT,
          int Num_Fragment,
          class Traits = std::char_traits<CharT>,
          class Allocator = std::allocator<CharT>
          >
class PSX_DefragWrite_Streambuff : public PSX_Write_Streambuff< CharT, Traits, Allocator>
{
public:
    PSX_DefragWrite_Streambuff(std::shared_ptr<hh::PSX_File> file_ptr, std::size_t size_buf = DEFULT_BUF_SIZE):
    PSX_Write_Streambuff< CharT, Traits, Allocator>(file_ptr, Num_Fragment * size_buf)
    {
    }
};


}
