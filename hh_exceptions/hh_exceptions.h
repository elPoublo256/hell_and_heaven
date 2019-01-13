#pragma once
#include <exception>
#include <errno.h>

namespace hell_and_haven {




class ErrnoException : public std::exception
{
  public:
    ErrnoException();
    const char* what();
private:
    int _errno = errno;

};

}
