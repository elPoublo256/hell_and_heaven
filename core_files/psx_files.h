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
namespace hh {

#define open_flag_t decltype(O_RDONLY)
#define lseek_t decltype(SEEK_END)
class PSX_File
{
public:

    PSX_File(){}
    PSX_File(const std::string& file_name, open_flag_t openflag);
    PSX_File(const PSX_File& copy) = delete;
    PSX_File(PSX_File && rv_copy);
    void operator =(const PSX_File& copy) = delete;
    virtual void lseek_from_begin(const long& num_bytes);
    virtual void lseek_from_qurent(const long& num_bytes);
    virtual void lseek_from_end(const long& num_bytes);
    virtual void psx_read(void* dest, const long num_bytes);
    virtual void psx_write(void* dest, const long num_bytes);
    void reset_flag_open(const int& new_flag);
    bool try_resrt_flag_open(const int& new_flag);
     virtual ~PSX_File();
protected:



friend void copy_psx_file(const PSX_File& origina, const PSX_File& copy,std::size_t size_bufer);

protected:
    void set_filedcripter(const int& fdr);
    int _file_descriptor = -1;
    open_flag_t _open_flag;
    long _curent_position;
private:
   virtual void _lseek(lseek_t flag, const long num_bytes);

};

void copy_psx_file(const PSX_File& origina, const PSX_File& copy, std::size_t size_bufer = 1024);



struct PSX_Fiel_Exc : public std::runtime_error
{
    PSX_Fiel_Exc(std::string wat) : runtime_error(wat){}
};

class PSX_Directory : public PSX_File
{
  public:
    PSX_Directory(const std::string& path);

private:
    std::string _path;
    std::set<std::string> files_names;
    std::set<std::string> dir_names;
};
void copy_psx_file(const PSX_Directory &origina, const PSX_Directory &copy, std::size_t size_bufer = 1024);
}
