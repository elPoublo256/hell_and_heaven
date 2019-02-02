#pragma once
#include <string.h>
#include <iterator>
#include <list>
#include <errno.h>
#include <unistd.h>
#include <iostream>
#include <memory>
#include "exception"
namespace hh {



class PSX_File
{
public:

    PSX_File(){}
    PSX_File(const int& fd);
    PSX_File(const std::string& file_name);

     virtual ~PSX_File(){}


friend void copy_psx_file(const PSX_File& origina, const PSX_File& copy,std::size_t size_bufer);

protected:
    void set_filedcripter(const int& fdr);
    int _file_descriptor = -1;

};

void copy_psx_file(const PSX_File& origina, const PSX_File& copy, std::size_t size_bufer = 1024);



struct PSX_Fiel_Exc : public std::runtime_error
{
    PSX_Fiel_Exc(std::string wat) : runtime_error(wat){}
};
}
