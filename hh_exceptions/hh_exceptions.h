#pragma once
#include <exception>
#include <errno.h>


class ErrnoException : public std::exception
{
  public:
    ErrnoException();
    const char* what() const override;
private:
    int _errno = errno;

};
