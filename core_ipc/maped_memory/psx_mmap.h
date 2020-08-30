#pragma once
#include <sys/mman.h>
#include <cstring>
#include "../../core_files/filesystem.h"
#include "../../hh_exceptions/hh_exceptions.h"
#include "../../core_base/psx_base_buffer.h"
#include <memory>
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
    Base_MappedMemeoryError() : hh::ErrnoException(){}

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
    int __fd;
    std::size_t& __offset;



  public:
    PSX_Base_MappedMemeory(const int& fd, const std::size_t& len,  void* addr = NULL, const std::size_t& offset = 0)
    {
        errno = 0;

        __ptr = mmap(addr, len, Protection, Flag, fd, offset);
        if(__ptr == MAP_FAILED)
        {
            throw Base_MappedMemeoryError();
        }

    }

    PSX_Base_MappedMemeory(const hh::core_files::Base_FS_File& file,
                           const std::size_t& len,// = hh::filesystem::FileAtributInfo(file).get_file_size(),
                           void* addr = NULL, const std::size_t& offset = 0)
    {
        errno = 0;

        __ptr = mmap(addr, len, Protection, Flag, file.get_file_discriptror(), offset);
        if(__ptr == MAP_FAILED)
        {
            throw Base_MappedMemeoryError();
        }
    }

    ~PSX_Base_MappedMemeory()
    {
        if(munmap(__ptr,__len)){//TODO what to do if return NO-ZERO
        }
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
