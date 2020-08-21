#pragma once
#include <sys/mman.h>
#include <cstring>
#include "../../core_files/filesystem.h"
#include "../../hh_exceptions/hh_exceptions.h"
#include "../psx_base_buffer.h"
#include <memory>
namespace hh {
namespace core_ipc {
enum MMapOpenFlg{
    ONLI_READ = PROT_READ,
    ONLI_WRITE = PROT_WRITE,

};

constexpr int RW_Flag = PROT_READ | PROT_WRITE;

enum MMapProtection
{
    Shared = MAP_SHARED,
    Ananim = MAP_ANONYMOUS,

};

class Base_MappedMemeoryError : public hh::ErrnoException
{

};



template <int Flag, int Protection, class T>
class PSX_Base_MappedMemeory : public hh::core_ipc::PSX_Base_Bufer
{
protected :
    PSX_Base_MappedMemeory(){}

private:


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

template <class T, int Flag = PROT_READ | PROT_WRITE>
class Shared_NoFile_MMap : public PSX_Base_MappedMemeory<Flag,MAP_ANONYMOUS | MAP_SHARED,T>
{
public:
    Shared_NoFile_MMap(const std::size_t len) : PSX_Base_MappedMemeory<Flag,MAP_ANONYMOUS | MAP_SHARED,T>
                           (-1,len,NULL,0) {}

};


}

}
