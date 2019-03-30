#pragma once
#include <vector>
#include <memory>
namespace hh {
namespace process{
namespace memory {

class VRAM_Manager
{
public:
    //!allocate size_buf bytes in heap-segment (alternativ malloc() )
    virtual void* vrm_malloc(std::size_t size_buf);
    //!resize allacated bufer in ptr (alternativ realloc() )
    virtual void* vrm_realloc(void* ptr, std::size_t new_size);

    //!remove bufer in ptr (alternative free() )
    virtual void vrm_free(void* ptr);

    //! allocate paje-fixedseize buf (alternativ posix_memalign() )
    virtual int vrm_posix_memalign(void **memptr, std::size_t aligment, std::size_t size);

    //! allocate in steck (alternativ alloca)
    virtual void* vrm_alloc_steck(std::size_t size);
};

/*
template <class T, class VR_M = VRAM_Manager>
class Allocator : public std::allocator<T>
{
    typedef unsigned int size_type;
     typedef unsigned int difference_type;
     typedef T value_type;
     typedef T* pointer;
     typedef T& reference;
     typedef const T* const_pointer;
     typedef const T& const_reference;
     typedef std::allocator<T> base_class;
public:
    VRAM_Manager __manager;
    Allocator(){}
    ~Allocator(){}
    T* allocate(size_type __n, const void *);
    void deallocate(T * p, std::size_t n);
    void construct(T* p, const T& val);
    void destroy(_Up *__p);

};
*/
}
}
}
