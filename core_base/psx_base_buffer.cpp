#include "psx_base_buffer.h"
#include <malloc.h>
#include <memory.h>

hh::PSX_Base_Bufer::PSX_Base_Bufer(const std::size_t &size) :
    __len(size)
{
    __ptr = alloc_mem_ptr(size);
}

hh::PSX_Base_Bufer::PSX_Base_Bufer(const hh::PSX_Base_Bufer &copy)
{
    __ptr = this->alloc_mem_ptr(copy.size_in_bytes());
    this->copy_mem(copy.get(),copy.size_in_bytes());
}

hh::PSX_Base_Bufer::PSX_Base_Bufer(PSX_Base_Bufer &&rv_copy) :

    __len(rv_copy.__len), __ptr(rv_copy.__ptr)

{

    rv_copy.__ptr = NULL;


}

hh::PSX_Base_Bufer::PSX_Base_Bufer(const std::size_t &size, void *ptr) : __ptr(ptr), __len(size)
{

}

hh::PSX_Base_Bufer::PSX_Base_Bufer(const char *str)
{
    auto len = strlen(str);
    __len = len;
    __ptr = malloc(len);
    memcpy(__ptr,(void*)str,len);
}

hh::PSX_Base_Bufer &hh::PSX_Base_Bufer::operator =(const hh::PSX_Base_Bufer& copy)
{
    if(this->is_valid())
    {
        this->delete_mem();
    }
    this->alloc_mem_ptr(copy.size_in_bytes());
    this->copy_mem(copy.get(),copy.size_in_bytes());
    return (*this);

}





void hh::PSX_Base_Bufer::resize(const std::size_t &len)
{
    //actiotly whe can and avarage size bufer
    if(len > __len)
    {
        throw std::out_of_range("error resize buser");
    }
    /* SIGSEGV;
    else
    {
        free(__ptr + len);
        __len = len;
    }
    */
    /* create new pointer
    __len = len;
    auto new_ptr = malloc(__len);
    memcpy(__ptr,new_ptr,__len);
    free(__ptr);
    __ptr = new_ptr;
    */
    __len = len;
    __ptr = realloc(__ptr,__len);


}

hh::PSX_Base_Bufer &hh::PSX_Base_Bufer::operator =(hh::PSX_Base_Bufer&& rv_copy)
{

    if(this->is_valid())
    {
        this->delete_mem();
    }
    __ptr = std::move(rv_copy.__ptr);
    __len = std::move(rv_copy.__len);
    return (*this);
}

void* hh::PSX_Base_Bufer::alloc_mem_ptr(const std::size_t &l)
{
    return malloc(l);
}

hh::PSX_Base_Bufer::~PSX_Base_Bufer()
{

    if(this->is_valid())
    {
        this->delete_mem();
    }
}

bool hh::PSX_Base_Bufer::is_valid(){return __ptr!=NULL;}

void hh::PSX_Base_Bufer::copy_mem(const void *src, const std::size_t &len)
{
   memcpy(__ptr,src,len);
}

void hh::PSX_Base_Bufer::delete_mem()
{

    free(__ptr);

    __ptr=NULL;
}
