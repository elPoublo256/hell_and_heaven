#include "psx_directory.h"
#include "../hh_exceptions/hh_exceptions.h"

hh::psx_file::PSX_Directory::PSX_Directory(const std::string& file_name, open_flag_t openflag)
{

    errno = 0;
    this->_file_descriptor = open(file_name.c_str(), openflag);
    if(_file_descriptor < 0)
    {
        if(errno != 0)
        {
            throw hh::ErrnoException();
        }
    }
    this->_dir_name = file_name;
    __flag = openflag;
}

void hh::psx_file::PSX_Directory::add_child_dir(const std::string &dirname,
                                           const permiss_t& mod) const
{
   if(mkdirat(_file_descriptor, dirname.c_str(), mod) == -1)
   {
       throw hh::ErrnoException();
   }

}

void hh::psx_file::PSX_Directory::change_dir(const std::string &file_name)
{
    close(_file_descriptor);
    this->_file_descriptor = open(file_name.c_str(), __flag);
    if(_file_descriptor < 0)
    {
        if(errno != 0)
        {
            throw hh::ErrnoException();
        }
    }
    this->_dir_name = file_name;
}
