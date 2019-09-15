#pragma once
#include <exception>
#include <errno.h>

namespace hh {





class ErrnoException : public std::exception
{
  public:
    ErrnoException();
    const char* what();
protected:
    int _errno = errno;
    auto get_error_code(){return _errno;}

};

class PermissionErr : public ErrnoException
{
public:
    PermissionErr() : ErrnoException(){}
};


}
