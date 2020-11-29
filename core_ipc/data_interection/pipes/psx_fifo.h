#pragma once
#include "../../../core_files/psx_files.h"

namespace hh {
namespace core_ipc {

class PSX_FIFO_Error : public hh::ErrnoException
{
public:
    PSX_FIFO_Error(const char* wht) : hh::ErrnoException(wht){}
};

class PSX_FIFO
{
public:
    PSX_FIFO(const char* name, const mode_t& mode = ALL_READ | ALL_WRIGHT);

    ~PSX_FIFO();
private:
    const char* __name;
};


}
}
