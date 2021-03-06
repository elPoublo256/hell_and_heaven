#include "hh_exceptions.h"
#include <string.h>
using namespace hh;

ErrnoException::ErrnoException() : std::runtime_error(strerror(errno))
{
    _errno = errno;
}

ErrnoException::ErrnoException(const char *what) :
    std::runtime_error(std::string(what) + std::string(" : ") +
                       std::string(strerror(errno)))
{

}



