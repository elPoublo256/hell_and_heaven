#include "../core_process/psx_setsignals.h"
#include "../core_process/psx_signalhandler.h"
#include <iostream>


int main()
{
    hh::core_process::BaseSignalHandler h([](int a){std::cout << "get signal";});
    return 0;

}
