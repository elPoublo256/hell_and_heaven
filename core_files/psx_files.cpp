#include "psx_files.h"


void hh::copy_psx_file(const PSX_File &original, const PSX_File &copy, std::size_t size_bufer)
{
    auto bufer = malloc(size_bufer);

    while (auto sreaded = read(original._file_descriptor, bufer, size_bufer) > 0)
    {
     if(write(copy._file_descriptor, bufer, sreaded) == sreaded)
     {
         throw hh::PSX_Fiel_Exc(std::string("fail copy file"));
     }
    }
    free(bufer);
}
