#pragma once
#include <vector>
#include <iterator>
#include <cstring>
namespace hh {






class PSX_Base_Bufer
{
public:
    PSX_Base_Bufer(){}
    PSX_Base_Bufer(const std::size_t& size);
    PSX_Base_Bufer(const std::size_t &size, void* ptr);// : __len(size), __ptr(ptr){}
    PSX_Base_Bufer(const PSX_Base_Bufer& copy);
    PSX_Base_Bufer(PSX_Base_Bufer&& rv_copy);

    template<typename T, typename _Traits, typename _Alloc>
    PSX_Base_Bufer(const std::basic_string<T, _Traits, _Alloc>& stdstr)
    {
        __len = stdstr.size() * sizeof(T);
        __ptr = malloc(__len);
        memcpy(__ptr,stdstr.data(), __len);

    }

    PSX_Base_Bufer(const char* str);
    virtual ~PSX_Base_Bufer();
    virtual const void* get() const {return const_cast<const void*> (__ptr);}
    void* get_ptr(){return __ptr;}
    virtual std::size_t size_in_bytes() const {return __len;}
    virtual bool is_valid();
    PSX_Base_Bufer& operator = (const PSX_Base_Bufer& copy);
    PSX_Base_Bufer& operator = (PSX_Base_Bufer&& rv_copy);
    void resize(const std::size_t& len);
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
     void* __ptr;
    void set_ptr(void* p) const {auto p_ptr = const_cast<void**>(&__ptr); *p_ptr=NULL;}
    void* get_p() const{ return __ptr;}
    std::size_t __len;

};
}



