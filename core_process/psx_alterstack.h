#pragma once
#include <memory>
#include <signal.h>



namespace hh {
namespace core_process {


template <class T>


class AlterAlloc: public std::allocator<T> , public stack_t

{
public:
public:
 template <class U > struct rebind { typedef AlterAlloc<U> other;};
 typedef unsigned int size_type;
 typedef unsigned int difference_type;
 typedef T value_type;
 typedef T* pointer;
 typedef T& reference;
 typedef const T* const_pointer;
 typedef const T& const_reference;
public:
 AlterAlloc(const AlterAlloc &cop){}
virtual ~AlterAlloc(){free(ss_sp);}
 T* allocate(int n);
 void deallocate(T* p, std::size_t n){}
 template <typename ...Args>
 void construct(T* p, const Args ...arg){ new((void *)p) T(arg...); }
 void destroy(T* p){((T*)p)->~T();}
 //struct sigstack
 //  {
 //    void *ss_sp;		/* Signal stack pointer.  */
 //    int ss_onstack;		/* Nonzero if executing on this stack.  */
 //  };
 T* main_pointer;
 T* move_pointer;



 AlterAlloc(const stack_t* other){}


 AlterAlloc(const std::size_t& size)
{

 ss_sp=malloc(size*sizeof(T));
 ss_size = size;
 main_pointer=reinterpret_cast<T *>(ss_sp);
 move_pointer=main_pointer;


}



};


}
}
