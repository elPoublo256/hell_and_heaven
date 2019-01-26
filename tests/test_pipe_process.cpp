
#include "../core_process/pipe_process.h"
#include "../core_process/prosess.h"
#include <iostream>
using namespace hh::process_core;

class PipeParent : public NoNamePipeProcess
{
public:


     int fake_main(const Exe_arg &arg) override
    {
        std::cout << "PARENT "<< __FUNCTION__ << std::endl;
        for(auto s : arg.argv_)
        {
            std::cout << s << std::endl;
        }
        return 0;
    }

};



class PipeChild : public NoNamePipeProcess
{
public:

    int fake_main(const Exe_arg &arg) override
   {
       std::cout << "CHILDe" << __FUNCTION__ << std::endl;
       for(auto s : arg.argv_)
       {
           std::cout << s << std::endl;
       }
       return 0;
   }
};
int main()
{
    PipeParent parent;


}
