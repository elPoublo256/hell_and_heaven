#pragma once
#include <fcntl.h>
#include <string>
#include <string.h>
#include <iterator>
#include <list>
#include <errno.h>
#include <unistd.h>
#include <iostream>

namespace hell_and_haven {


class OpenFileError : public std::exception
{
public:
    OpenFileError(){}
    ~OpenFileError(){}
    std::string err_what;
    decltype(EEXIST) error_open;
    const char* what() {return err_what.c_str();}
    OpenFileError(const decltype(errno) &error_erno);
    OpenFileError(const int &&error_erno);

private:
    void set_error_what(const decltype(errno) &error_erno);
};

class PSX_File
{
public:

    PSX_File(){}
    virtual ~PSX_File(){}



protected:
    void set_filedcripter(const int& fdr);
    int _file_descriptor;

};


class Base_IFile_Stream : public PSX_File
{
	public:
    Base_IFile_Stream(const int& file_descriptor, const int& pos = 0 );
    Base_IFile_Stream(const std::string &file_name);
    Base_IFile_Stream(const Base_IFile_Stream &copy) = delete;
    Base_IFile_Stream(const char*  c_name);
    void operator = (const Base_IFile_Stream &copy) = delete;

public:
template <class T>
Base_IFile_Stream& operator >> (T& arg) {
    int len = sizeof(T);
    void* dest = &arg;
    ssize_t ret = 0;
    while (len != 0 && (ret = read(_file_descriptor, dest, len)) != 0)
    {
        if(ret == -1)
        {
         throw OpenFileError(errno);
        }
        len -= ret;
    }
	return *this;
}

	private:
	int cure_descripter;

};

class Base_OFile_Stream : public PSX_File
{
public:
    Base_OFile_Stream(int file_descriptor );
    Base_OFile_Stream(std::string &file_name, int flag = O_TRUNC);
    Base_OFile_Stream(std::string && file_name, int flag = O_TRUNC);
    Base_OFile_Stream(const Base_OFile_Stream &copy) = delete;
    void operator = (const Base_OFile_Stream &copy) = delete;
    std::list<int> list_errno;
    template <class T>
    Base_OFile_Stream& operator << (const T &arg)
    {
      lseek(_file_descriptor, 0, SEEK_END);
      write(_file_descriptor, &arg, sizeof(T) );
      fsync(_file_descriptor);
      return *this;
    }
protected:
 int cure_descripter;
};


}
