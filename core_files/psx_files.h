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
namespace hh {

#define open_flag_t decltype(O_RDONLY)

class PSX_File
{
public:

    PSX_File(){}
    PSX_File(const std::string& file_name, open_flag_t openflag);
    PSX_File(const PSX_File& copy) = delete;
    PSX_File(PSX_File && rv_copy);
    void operator =(const PSX_File& copy) = delete;
    void lseek_from_begin(const long& nub_bytes);
    void lseek_from_qurent(const long& nub_bytes);
    void lseek_from_end(const long& nub_bytes);
    void read(void* dest, const long nu_bytes);
    void write(void* dest, const long nu_bytes);
     virtual ~PSX_File(){}
protected:



friend void copy_psx_file(const PSX_File& origina, const PSX_File& copy,std::size_t size_bufer);

protected:
    void set_filedcripter(const int& fdr);
    int _file_descriptor = -1;
    open_flag_t _open_flag;
    long _curent_position;

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
