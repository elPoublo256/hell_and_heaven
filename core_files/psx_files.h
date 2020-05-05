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
namespace hh {
namespace psx_file {

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

class BasePSXFile
{
public:
    BasePSXFile(const int& file_discriptor)
    {
        _file_descriptor = file_discriptor;
    }
    int get_file_discriptror() const {return _file_descriptor;}
    virtual ~BasePSXFile(){close(_file_descriptor);}
protected:
    BasePSXFile(){}
 int _file_descriptor = -1;



};

//!
//! \brief The PSX_File class
//!this class provide low level interface for working with files
//! using system comands
class PSX_File : public BasePSXFile
{
public:

    PSX_File(){}
    PSX_File(const std::string& file_name, open_flag_t openflag = O_RDONLY);
    PSX_File(const std::string& file_name, open_flag_t openflag,
             permiss_t permiss);
    PSX_File(const PSX_File& copy) = delete;
    PSX_File(PSX_File &&rv_copy);
    void operator =(const PSX_File& copy) = delete;
    virtual void lseek_from_begin(const long& num_bytes);
    virtual void lseek_from_qurent(const long& num_bytes);
    virtual void lseek_from_end(const long& num_bytes);

    virtual void psx_read(void* dest, const long num_bytes);
    virtual void psx_write(void* dest, const long num_bytes);
    virtual void psx_defragment_read(const iovec *iov, int count_iov);
    virtual void psx_defragment_write(const iovec *iov, int count_iov);
    virtual void data_fsink();
    void flash();
    auto get_name(){return this->__filename;}


    void reset_flag_open(const int& new_flag);
    bool try_resrt_flag_open(const int& new_flag) noexcept;

    PSX_File&& make_duplicate();//using dup

     void psx_close();
     virtual ~PSX_File();
protected:



friend void copy_psx_file(const PSX_File& origina, const PSX_File& copy,std::size_t size_bufer);

protected:
PSX_File(int fd) : BasePSXFile(fd) {}
    void set_filedcripter(const int& fdr);
    std::string __filename;

    open_flag_t _open_flag;
    long _curent_position;
private:
   virtual void _lseek(lseek_t flag, const long num_bytes);


};

class PSX_Temprorary_File : public PSX_File
{
public:

    PSX_Temprorary_File(std::string teplate_fn);
    ~PSX_Temprorary_File();
 protected:
    std::string _filename;
};


void copy_psx_file(const PSX_File& origina, const PSX_File& copy, std::size_t size_bufer = 1024);



struct PSX_Fiel_Exc : public std::runtime_error
{
    PSX_Fiel_Exc(std::string wat) : runtime_error(wat){}
};

}
}
