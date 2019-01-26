#pragma once
#include <exception>
#include <errno.h>

namespace hh {




class ErrnoException : public std::exception
{
  public:
    ErrnoException();
    const char* what();
private:
    int _errno = errno;

};

}
