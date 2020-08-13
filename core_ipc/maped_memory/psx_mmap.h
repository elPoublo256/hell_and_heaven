#pragma once
#include <sys/mman.h>
#include <cstring>
#include "../../core_files/filesystem.h"
#include "../../hh_exceptions/hh_exceptions.h"
#include <memory>
namespace hh {
namespace core_ipc {


class Base_MappedMemeoryError : public hh::ErrnoException
{

};



template <int Flag, int Protection>
class PSX_Base_MappedMemeory
{
private:
    void* __ptr;
    std::size_t __len;


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

    PSX_Base_MappedMemeory(const hh::psx_file::BasePSXFile& file,
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
    void* get_real_ptr() const {return __ptr;}
};



/* TODO Experimants
template <int Flag, int Protection, class T>
class PSX_Base_MappedMemeoryAllocator  : public std::allocator<T>, public PSX_Base_MappedMemeory
{

}
*/




}

}
