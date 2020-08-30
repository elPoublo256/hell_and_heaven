#pragma once
#include <vector>
#include <iterator>

namespace hh {



namespace core_ipc {


class PSX_Base_Bufer
{
public:
    PSX_Base_Bufer(){}
    PSX_Base_Bufer(std::size_t& size);
    PSX_Base_Bufer(const PSX_Base_Bufer& copy);
    PSX_Base_Bufer(PSX_Base_Bufer&& rv_copy);
    virtual ~PSX_Base_Bufer();
    virtual const void* get() const {return const_cast<const void*> (__ptr);}
    virtual std::size_t size_in_bytes() const {return __len;}
    virtual bool is_valid();
    PSX_Base_Bufer& operator = (const PSX_Base_Bufer& copy);
    PSX_Base_Bufer& operator = (PSX_Base_Bufer&& rv_copy);
protected:
    ///return pointer allocated memory. malloc in defualt
    /// call in PSX_Base_Bufer(std::size_t& size)
    virtual void* alloc_mem_ptr(const std::size_t& l);
    ///copy memory from pointer. memcpy in default
    /// call in PSX_Base_Bufer(const PSX_Base_Bufer& copy)
    virtual void copy_mem(const void* src, const std::size_t &len);
    ///delete alacated memory. defaut free()
    /// call in distructor
    virtual void delete_mem();
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
