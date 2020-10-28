#pragma once
#include <sys/mman.h>
#include <cstring>
#include "../../hh_exceptions/hh_exceptions.h"
#include "../../core_base/psx_base_buffer.h"
#include "../../core_base/psx_base_file.h"
#include <sys/mman.h>
namespace hh {
namespace core_ipc {
enum MMapOpenFlg{
    ONLI_READ = PROT_READ,
    ONLI_WRITE = PROT_WRITE,
    ONLY_EXUCATE =PROT_EXEC

};

//constexpr int RW_Flag = PROT_READ | PROT_WRITE;

enum MMapProtection
{
    Shared = MAP_SHARED,
    Ananim = MAP_ANONYMOUS,

};

class Base_MappedMemeoryError : public hh::ErrnoException
{
public:
    inline Base_MappedMemeoryError() : hh::ErrnoException(){}
    inline Base_MappedMemeoryError(const char* str) : hh::ErrnoException(str){}


};



template <int Flag, int Protection>
class PSX_Base_MappedMemeory :  public hh::PSX_Base_Bufer
{
protected :
    PSX_Base_MappedMemeory(){}
    void delete_mem() override
    {
        munmap(__ptr,__len);
    }

    void *alloc_mem_ptr(const std::size_t &l) override
    {
        void* ptr = mmap(__ptr, l, Protection, Flag, __fd, __offset);
        if(ptr == MAP_FAILED)
        {
            throw Base_MappedMemeoryError();
        }

    }

private:

    std::size_t __offset;
    int __fd;


  public:
    PSX_Base_MappedMemeory(const int& fd, const std::size_t& len,  void* addr = NULL, const std::size_t& offset = 0)
    {
        errno = 0;

        __ptr = mmap(addr, len, Protection, Flag, fd, offset);
        if(__ptr == MAP_FAILED)
        {
            throw Base_MappedMemeoryError("error mmap");
        }

    }

    PSX_Base_MappedMemeory(const hh::BaseOpen<int>&  file,
                           const std::size_t& len,// TODO = hh::filesystem::FileAtributInfo(file).get_file_size(),
                           void* addr = NULL, std::size_t offset = 0)
    {
        errno = 0;


        __ptr = mmap(addr, len, Protection, Flag, file.get_file_discriptror(), offset);
        if(__ptr == MAP_FAILED)
        {
            throw Base_MappedMemeoryError("error mmap");
        }
    }

    ~PSX_Base_MappedMemeory()
    {
    }


};



/* TODO Experimants
template <int Flag, int Protection, class T>
class PSX_Base_MappedMemeoryAllocator  : public std::allocator<T>, public PSX_Base_MappedMemeory
{

}
*/



}

}
