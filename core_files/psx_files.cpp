#include "psx_files.h"
#include <iostream>
#include "../hh_exceptions/hh_exceptions.h"

//-------------------------Files move constructors-------------------
hh::core_files::Read_FS_File::Read_FS_File(Read_FS_File &&rv) :
    hh::BaseFDReader(rv.__fd){}

hh::core_files::Write_FS_File::Write_FS_File(Write_FS_File &&rv) :
    hh::BaseFDWriter(rv.__fd){}

hh::core_files::ReadWrite_FS_File:: ReadWrite_FS_File( ReadWrite_FS_File &&rv) :
    hh::BaseFDReaderWriter(rv.__fd){}



//-----------------------Files open constructors--------------------------

hh::core_files::Read_FS_File::Read_FS_File(const char *name,
                                           int flag_open,
                                           const mode_t &mod)
{
    int fd;
    if(mod){fd = open(name,O_RDONLY | flag_open ,mod);}
    else
    {
        fd = open(name,O_RDONLY | flag_open);
    }

    if(fd < 0)
    {
        throw FS_File_Error("error open file");
    }
    __fd = fd;
}

hh::core_files::Write_FS_File::Write_FS_File(const char *name,
                                           int flag_open,
                                           const mode_t &mod)
{
    auto fd = open(name,O_WRONLY | flag_open ,mod);
    if(fd < 0)
    {
        throw FS_File_Error("error open file");
    }
    __fd = fd;
}

hh::core_files::ReadWrite_FS_File::ReadWrite_FS_File(const char *name,
                                           int flag_open,
                                           const mode_t &mod) : BaseFDReaderWriter()
{
    auto fd = open(name,O_RDWR | flag_open ,mod);
    if(fd < 0)
    {
        throw FS_File_Error("error open file");
    }
    __fd = fd;
}



//------------------------------FUBRIC-------------------------
hh::core_files::FS_File_Fubric::FS_File_Fubric(const char *name,
                                               int flag,
                                               const mode_t &open_mode) :
    __name(name), __addation_flag(flag), __mode_open(open_mode)
{

}


hh::core_files::Read_FS_File&&
hh::core_files::FS_File_Fubric::create_read_fs_file(const char* name)
{
    return std::move(Read_FS_File(name,__addation_flag, __mode_open));
}


hh::core_files::Write_FS_File&&
hh::core_files::FS_File_Fubric::create_write_fs_file(const char* name)
{
    return std::move(Write_FS_File(name,__addation_flag, __mode_open));
}

hh::core_files::ReadWrite_FS_File&&
hh::core_files::FS_File_Fubric::create_readwrite_fs_file(const char *name)
{
    return std::move(ReadWrite_FS_File(name,__addation_flag,__mode_open));
}


hh::read_f_ptr hh::core_files::FS_File_Fubric::get_read()
{
    return std::make_shared<BaseReader>
            (this->create_read_fs_file(__name.c_str()));
}
hh::write_f_ptr hh::core_files::FS_File_Fubric::get_write()
{
    return std::make_shared<BaseWriter>
            (this->create_write_fs_file(__name.c_str()));
}

hh::rdwr_f_ptr  hh::core_files::FS_File_Fubric::get_readwrite()
{
    return std::make_shared<BaseReadWrite>
            (this->create_readwrite_fs_file(this->__name.c_str()));
}

