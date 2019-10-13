#pragma once
//#include "psx_files.h"
//#include <streambuf>
//#include <memory>
//#include <fstream>
//#include <cstring>

//namespace hh {

//#define DEFULT_BUF_SIZE 3
//template <class CharT = uint8_t,
//          class Traits = std::char_traits<CharT>,
//          class Allocator = std::allocator<CharT>
//          >
//class PSX_Read_Streambuff : public std::basic_streambuf<CharT, Traits>
//{
//public:
//    typedef CharT                               char_type;
//    typedef Traits                              traits_type;
//    typedef typename traits_type::int_type 		int_type;
//    typedef typename traits_type::pos_type 		pos_type;
//    typedef typename traits_type::off_type 		off_type;
//    using Base = std::basic_streambuf<CharT, Traits>;

//    PSX_Read_Streambuff(std::shared_ptr<hh::PSX_File> file_ptr, std::size_t size_buf = DEFULT_BUF_SIZE):
//        __psx_file_ptr(file_ptr)
//    {
//        __bufer.resize(size_buf);

//        __psx_file_ptr->psx_read(__bufer.data(), __bufer.size() * sizeof(CharT));
//        this->_M_in_beg = this->_M_in_cur = __bufer.data();
//        this->_M_in_end = __bufer.data() + __bufer.size();
//    }

//    PSX_Read_Streambuff(std::string file_name,
//                         permiss_t permis = ALL_READ | ALL_WRIGHT,
//                         std::size_t size_buf = DEFULT_BUF_SIZE) :
//    __psx_file_ptr(new PSX_File(file_name, O_WRONLY | O_CREAT, permis))
//    {
//        __bufer.resize(size_buf);
//        Base::setp(__bufer.data(), __bufer.data() + __bufer.size());
//        this->_M_out_cur = __bufer.data();
//    }
//protected:

//    virtual int_type uflow()
//    {
//        std::cout<<__FUNCTION__<<std::endl;
//        Base::uflow();
//    }
//virtual int_type underflow()
//    {
//        std::cout<<__FUNCTION__<<std::endl;
//        __psx_file_ptr->psx_read(__bufer.data(), __bufer.size() * sizeof(CharT));
//        this->_M_in_beg = this->_M_in_cur = __bufer.data();
//        this->_M_in_end = __bufer.data() + __bufer.size();
//        for(auto a : __bufer)
//        {
//            std::cout<<"a = "<<a<<std::endl;
//        }
//        return Base::underflow();
//    }
//private:
//    std::shared_ptr<hh::PSX_File> __psx_file_ptr;
//    std::vector<CharT, Allocator> __bufer;
//};


//}
