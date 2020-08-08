#include "hh_exceptions.h"
#include <string.h>
using namespace hh;

ErrnoException::ErrnoException() : std::runtime_error(strerror(errno))
{
    _errno = errno;
}



