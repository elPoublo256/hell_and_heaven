#include "../core_thread/psx_thread.h"
#include <iostream>
#include <thread>

int foo(int a, int b)
{

    std::cout<< "a="<<a<<" b="<<b<<std::endl;
}

static void* bar(void* ar)
{
    std::cout<<"THIS IS Base_PSX_Thread"<<std::endl;
}

template <class T>
class A
{
public:
    void foo()
    {
        std::cout<<"A"<<std::endl;
    }
    static void* bar(void* arg)
    {
        A* ptr = (A*)arg;
        ptr->foo();
    }
};

int main()
{
   // hh::threads::Base_PSX_Thread bt(bar);
   // bt.run(NULL);
   // bt.join_no_res();
    hh::threads::Base_PSX_Thread btt(A<int>::bar);
    btt.run(NULL);
    btt.join_no_res();

    hh::threads::PSX_Thread<int,int,int> t(foo);
    t.run(5,9);
    //t.join_no_res();


    return 0;
}
