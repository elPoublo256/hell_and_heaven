#include "psx_fifo.h"
#include <stdio.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>


hh::core_ipc::PSX_FIFO::PSX_FIFO(const char* name, const mode_t& mode) : __name(name)
{
    if(mkfifo(name, mode))
    {
        throw  PSX_FIFO_Error("error create FIFO");
    }
}

hh::core_ipc::PSX_FIFO::~PSX_FIFO()
{
    unlink(__name);
}
