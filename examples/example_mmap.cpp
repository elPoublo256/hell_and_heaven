#include "../core_ipc/maped_memory/psx_mmap.h"
#include "../core_files/psx_files.h"
#include <vector>
#include <iostream>
int main()
{
    std::vector<int> v;
    v.reserve(10);
    for(int i = 0; i < 10; i++)
    {
        v.push_back(i);
    }
    {
         hh::core_files::Write_FS_File wf("wh.txt");
        wf.psx_write(v.data(),sizeof(int) * v.size());
    }

    hh::core_files::ReadWrite_FS_File f("wh.txt");
    hh::core_ipc::PSX_Base_MappedMemeory<PROT_READ | PROT_WRITE, MAP_SHARED>
            map(f.get_file_discriptror(),sizeof(int) * 10 ,NULL,0);

    std::vector<int> v2;
    v2.resize(10);
    memcpy(v2.data(), map.get(), sizeof (int) * 10);

    for(auto i : v2)
    {
        std::cout<<"i="<<i<<std::endl;
    }
    remove("wh.txt");
    return 0;
}
