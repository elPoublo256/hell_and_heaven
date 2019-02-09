#include "psx_files.h"
#include <unistd.h>
hh::PSX_File::PSX_File(const std::string &file_name, open_flag_t openflag)
{

}


void hh::PSX_File::lseek_from_begin(const long &nub_bytes)
{

}

void hh::PSX_File::lseek_from_qurent(const long &nub_bytes)
{

}

void hh::PSX_File::lseek_from_end(const long &nub_bytes)
{

}

void hh::copy_psx_file(const PSX_File &original, const PSX_File &copy, std::size_t size_bufer)
{
    if(size_bufer != 0)
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
    return;
    }
    else {
        throw hh::PSX_Fiel_Exc(std::string("Zero size bufer"));
    }
}

hh::PSX_Directory::PSX_Directory(const std::string &path) :  PSX_File(path, O_DIRECTORY)
{

}

void hh::copy_psx_file(const PSX_Directory &origina, const PSX_Directory &copy, std::size_t size_bufer)
{

}
