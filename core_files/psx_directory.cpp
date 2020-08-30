#include "psx_directory.h"
#include "../hh_exceptions/hh_exceptions.h"

hh::core_files::PSX_Directory::PSX_Directory(const std::string& file_name, open_flag_t openflag)
{

    errno = 0;
    this->__fd = open(file_name.c_str(), openflag);
    if(__fd < 0)
    {
        if(errno != 0)
        {
            throw hh::ErrnoException();
        }
    }
    this->_dir_name = file_name;
    __flag = openflag;
}

void hh::core_files::PSX_Directory::add_child_dir(const std::string &dirname,
                                           const permiss_t& mod) const
{
   if(mkdirat(__fd, dirname.c_str(), mod) == -1)
   {
       throw hh::ErrnoException();
   }

}

void hh::core_files::PSX_Directory::change_dir(const std::string &file_name)
{
    close(__fd);
    this->__fd = open(file_name.c_str(), __flag);
    if(__fd < 0)
    {
        if(errno != 0)
        {
            throw hh::ErrnoException();
        }
    }
    this->_dir_name = file_name;
}
