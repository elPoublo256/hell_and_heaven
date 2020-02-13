#pragma once
#include <memory>
#include <functional>
namespace hh {
namespace core_process {

}

namespace smart_functor {


template <class Functor, typename ResType, typename... Args>
class StaticFunctor
{
   private:

public:
   static Functor* owner_ptr;
   static ResType action(Args ...args){ return owner_ptr->action(args...);}
   static void set_owner(Functor* ptr){owner_ptr = ptr;}
};





template <class SelfType,  typename ResType, typename... Args>
class Smart_Functor
{
    public:

    typedef StaticFunctor<SelfType,ResType,Args...> StatFunct;
    virtual void set_owner(SelfType* ptr)
    {
        StaticFunctor<SelfType,ResType,Args...>::set_owner(ptr);
    }

    virtual ResType action(Args ...args){}

    Smart_Functor(){set_owner((SelfType*) this);}

    auto get_static_action() {auto res = [](Args... args)->ResType
        {return StaticFunctor<SelfType,ResType,Args...>::action(args...);} ;return res;}

};
}
}



#define INITT_STATIC_OWNER(CLASS) template<> CLASS* CLASS::StatFunct::owner_ptr = NULL

