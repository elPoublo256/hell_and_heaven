#pragma once
#include <stdexcept>
#include <errno.h>

namespace hh {





class ErrnoException : public std::runtime_error
{
  public:
    ErrnoException();
    ErrnoException(const char* what);
    int _errno = errno;
    int get_error_code(){return _errno;}


};

class PermissionErr : public ErrnoException
{
public:
    PermissionErr() : ErrnoException(){}
};


}
