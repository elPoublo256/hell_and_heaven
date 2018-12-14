#pragma once
#include <fcntl.h>
#include <string>
#include <string.h>
#include <iterator>
#include <list>
#include <errno.h>
#include <unistd.h>
#include <iostream>

class PSX_File
{
public:
    class OpenFileError : public std::exception
    {
    public:
        decltype(EEXIST) error_open;
        OpenFileError( decltype(errno) error_erno);
    };
    PSX_File(){}
    virtual int filedcripter() const {return fd;}
protected:
    void set_filedcripter(const int& fdr);
    int fd;

};


class Base_IFile_Stream : public PSX_File
{
	public:
    Base_IFile_Stream(const int& file_descriptor, const int& pos = 0 );
    Base_IFile_Stream(const std::string &file_name);
    Base_IFile_Stream(const Base_IFile_Stream &copy) = delete;
    Base_IFile_Stream(const char*  c_name);
    void operator = (const Base_IFile_Stream &copy) = delete;

template <class T>
Base_IFile_Stream& operator >> (T& arg) {
    int len = sizeof(T);
    void* dest = &arg;
    ssize_t ret = 0;
    while (len != 0 && (ret = read(filedcripter(), dest, len)) != 0)
    {
        if(ret == -1)
        {
            if(errno == EINTR)
                continue;
            std::cout <<"errno ="<<errno << std::endl;
            break;
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
    Base_OFile_Stream& operator << (T &arg)
    {
      lseek(cure_descripter, 0, SEEK_END);
      write(filedcripter(), &arg, sizeof(T) );
      fsync(cure_descripter);
      return *this;
    }


private:
 int cure_descripter;
};



