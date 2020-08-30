#pragma once
#include <string.h>
#include <iterator>
#include <list>
#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <memory>
#include "exception"
#include <sys/stat.h>
#include <fcntl.h>
#include <set>
#include <unistd.h>
#include <vector>
#include <sys/uio.h>
#include "../core_base/psx_base_file.h"
#include "../hh_exceptions/hh_exceptions.h"



#include <iostream>
namespace hh {
namespace core_files {

#define WRITE_ONLY O_WRONLY
#define READ_ONLY O_RDONLY
//#define open_flag_t decltype(O_RDONLY)
#define open_flag_t int
//#define lseek_t decltype(SEEK_END)
#define lseek_t int
//#define permiss_t decltype(S_IRUSR)
#define permiss_t  int
#define ALL_READ S_IRUSR | S_IRGRP | S_IROTH
#define ALL_WRIGHT S_IWGRP | S_IWUSR | S_IWOTH
#define ONLY_USER_READ_WRIGHT S_IRUSR | S_IWUSR
class FS_File_Error : public hh::BaseFDErrorFile
{
public:
    FS_File_Error(const char* what) : hh::BaseFDErrorFile(what){}
};




class Read_FS_File : public BaseFDReader
{
public:
    Read_FS_File(){}
    Read_FS_File(const int& fd) : BaseFDReader(fd){}
    Read_FS_File(const Read_FS_File& copy) = delete;
    Read_FS_File(Read_FS_File&& rv);
    Read_FS_File(const char* name, int flag_open = 0, const mode_t& mod = 0);

    virtual ~Read_FS_File(){}

};

class Write_FS_File : public BaseFDWriter
{
public:
    Write_FS_File(){}
    Write_FS_File(const int& fd) : BaseFDWriter(fd){}
    Write_FS_File(const Write_FS_File& copy) = delete;
    Write_FS_File(Write_FS_File&& rv);
    Write_FS_File(const char* name, int flag_open = O_CREAT, const mode_t& mod = 0777);

};

class ReadWrite_FS_File : public BaseFDReaderWriter
{
public:
    ReadWrite_FS_File(){}
    ReadWrite_FS_File(const int& fd) : BaseFDReaderWriter(fd){}
    ReadWrite_FS_File(const ReadWrite_FS_File& copy) = delete;
    ReadWrite_FS_File(ReadWrite_FS_File&& rv);
    ReadWrite_FS_File(const char* name, int flag_open = O_CREAT, const mode_t& mod = 0777);
    virtual ~ReadWrite_FS_File(){}
};

class FS_File_Fubric : public hh::FubricReadWriteFiles
{
public:
    FS_File_Fubric(const char* name = "./", int flag = O_CREAT,
                   const mode_t& open_mode = ALL_READ | ALL_WRIGHT);

    Read_FS_File&& create_read_fs_file(const char* name);
    Write_FS_File&& create_write_fs_file(const char* name);
    ReadWrite_FS_File&& create_readwrite_fs_file(const char* name);

    read_f_ptr get_read() override;
    write_f_ptr get_write() override;
    rdwr_f_ptr get_readwrite() override;
    virtual ~FS_File_Fubric(){}


private:
    int __addation_flag;
    mode_t __mode_open;
    std::string __name;



};






}
}
