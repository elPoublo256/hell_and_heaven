#pragma once
#include <vector>
#include <iterator>
namespace hh {



namespace core_ipc {

class PSX_Base_Bufer
{
public:
    virtual const void* get(){return const_cast<const void*> (__ptr);}
    virtual std::size_t size_in_bytes(){return __len;}
private:
    void* __ptr;
    std::size_t __len;

};

template <class T>
class PSX_TBaseBufer : PSX_Base_Bufer
{
public:
    //typedef
    //class Iterator : public std::vector<T>::iterator
   // {
   //     Iterator(T* ptr) : std::vector<T>::iterator{
   // };

    void data() {return (T*)__ptr;}
    //TODO make like stl-container
    //class Iterator : public std::
};

}
}
