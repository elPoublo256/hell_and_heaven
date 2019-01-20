
#include "../core_process/pipe_process.h"
#include "../core_process/prosess.h"
#include <iostream>
/*using namespace hell_and_haven::process_core;
class PipeParent : public NoNamePipeProcess
{
public:
    PipeParent() : NoNamePipeProcess(get_main_ptr()) {}
     int fake_main(const Exe_arg &arg) override
    {
        std::cout << "PARENT "<< __FUNCTION__ << std::endl;
        for(auto s : arg.argv_)
        {
            std::cout << s << std::endl;
        }
    }
};



class PipeChild : public NoNamePipeProcess
{
    int fake_main(const Exe_arg &arg) override
   {
       std::cout << "CHILDe" << __FUNCTION__ << std::endl;
       for(auto s : arg.argv_)
       {
           std::cout << s << std::endl;
       }
   }
};*/
int main()
{
    //PipeParent parent;
   // auto p = make_piped_processes<PipeParent, PipeChild>();


}
