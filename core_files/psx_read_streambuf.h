#pragma once
#include "psx_files.h"
#include <streambuf>
#include <memory>
#include <fstream>
#include <cstring>

namespace hh {


template <class CharT = uint8_t,
          class Traits = std::char_traits<CharT>,
          class Allocator = std::allocator<CharT>
          >
class PSX_Read_Streambuff : public std::basic_streambuf<CharT, Traits>
{
public:

protected:

private:
    std::shared_ptr<hh::PSX_File> __psx_file_ptr;
    std::vector<CharT, Allocator> __bufer;
};


}
