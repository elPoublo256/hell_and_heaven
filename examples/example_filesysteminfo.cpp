
#include "../core_files/filesystem.h"
#include <iostream>

int main()
{
    hh::filesystem::FileSystemInfo info("./");
    std::cout << "num_blocks_in_fylesystem: "<<
                 info.num_blocks_in_fylesystem()
              <<std::endl;

}
