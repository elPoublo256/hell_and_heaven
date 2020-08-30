#include "psx_base_buffer.h"
#include <malloc.h>
#include <memory.h>
hh::core_ipc::PSX_Base_Bufer::PSX_Base_Bufer(std::size_t &size) :
    __len(size)
{
    __ptr = alloc_mem_ptr(size);
}

hh::core_ipc::PSX_Base_Bufer::PSX_Base_Bufer(const hh::core_ipc::PSX_Base_Bufer &copy)
{
    __ptr = this->alloc_mem_ptr(copy.size_in_bytes());
    this->copy_mem(copy.get(),copy.size_in_bytes());
}

hh::core_ipc::PSX_Base_Bufer &hh::core_ipc::PSX_Base_Bufer::operator =(const hh::core_ipc::PSX_Base_Bufer& copy)
{
    if(this->is_valid())
    {
        this->delete_mem();
    }
    this->alloc_mem_ptr(copy.size_in_bytes());
    this->copy_mem(copy.get(),copy.size_in_bytes());
    return (*this);

}

hh::core_ipc::PSX_Base_Bufer &hh::core_ipc::PSX_Base_Bufer::operator =(hh::core_ipc::PSX_Base_Bufer&& rv_copy)
{

    if(this->is_valid())
    {
        this->delete_mem();
    }
    __ptr = std::move(rv_copy.__ptr);
    __len = std::move(rv_copy.__len);
    return (*this);
}

void* hh::core_ipc::PSX_Base_Bufer::alloc_mem_ptr(const std::size_t &l)
{
    return malloc(l);
}

bool hh::core_ipc::PSX_Base_Bufer::is_valid(){return __ptr!=NULL;}

void hh::core_ipc::PSX_Base_Bufer::copy_mem(const void *src, const std::size_t &len)
{
   memcpy(__ptr,src,len);
}

void hh::core_ipc::PSX_Base_Bufer::delete_mem()
{
    free(__ptr);
    __ptr=NULL;
}
