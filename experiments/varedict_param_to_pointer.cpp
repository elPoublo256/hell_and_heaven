#include <iostream>
#include <stdarg.h>
#include <thread>
void* bar(void* args)
{
    return NULL;
}

template<class ...Args>
class foo
{
public:
    //va_list _args;
    foo(Args... args)
    {
        //va_start(_args,args);
    }


};

int main()
{
    foo<int,int,int> f(1,2,3);
    return 0;
}
