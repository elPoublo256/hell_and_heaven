#include "vir_mem.h"
#include <stdlib.h>
void* hh::process::memory::VRAM_Manager::vrm_malloc(std::size_t size_buf)
{
    return malloc(size_buf);
}

void hh::process::memory::VRAM_Manager::vrm_free(void *ptr)
{
    free(ptr);
}

void* hh::process::memory::VRAM_Manager::vrm_realloc(void *ptr, std::size_t new_size)
{
    return realloc(ptr, new_size);
}

int hh::process::memory::VRAM_Manager::vrm_posix_memalign(void **memptr,
                                                          std::size_t aligment,
                                                          std::size_t size)
{
    return posix_memalign(memptr,aligment,size);
}

void* hh::process::memory::VRAM_Manager::vrm_alloc_steck(std::size_t size)
{
#if __GNUC__
    return alloca(size);
#else
    return NULL;
#endif
}
