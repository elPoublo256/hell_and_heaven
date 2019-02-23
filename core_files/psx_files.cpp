#include "psx_files.h"

#include "../hh_exceptions/hh_exceptions.h"
hh::PSX_File::PSX_File(const std::string &file_name, open_flag_t openflag)
{

}


void hh::PSX_File::_lseek(lseek_t flag, const long num_bytes)
{
    auto new_pos = lseek(_file_descriptor,num_bytes, flag);
    if((new_pos - _curent_position) == num_bytes)
    {
        _curent_position = new_pos;
    }
    else
    {
        throw hh::ErrnoException();
    }

}
void hh::PSX_File::lseek_from_begin(const long &num_bytes)
{
  if(num_bytes < 0)
  {
      throw(PSX_Fiel_Exc("num seek from begin less 0"));
  }
  else
  {
      _lseek(SEEK_SET,num_bytes);
  }
}

void hh::PSX_File::lseek_from_qurent(const long &num_bytes)
{
  _lseek(SEEK_CUR, num_bytes);
}

void hh::PSX_File::lseek_from_end(const long &num_bytes)
{
 _lseek(SEEK_END, num_bytes);
}

void hh::PSX_File::psx_read(void *dest, const long num_bytes)
{
    auto res = read(_file_descriptor,dest,num_bytes);
    if(res < 0)
    {
        throw hh::ErrnoException();
    }
}

void hh::PSX_File::psx_write(void *dest, const long num_bytes)
{

    auto res = write(_file_descriptor,dest,num_bytes);
    if(res < 0)
    {
        throw hh::ErrnoException();
    }
}

hh::PSX_File::~PSX_File()
{
    close(_file_descriptor);
}

void hh::PSX_File::reset_flag_open(const int &new_flag)
{
   int res = fcntl( _file_descriptor, F_SETFL, new_flag);
   if(res != -1)
   {
       _open_flag = fcntl(_file_descriptor, F_GETFL);
   }
   else
   {
       throw hh::ErrnoException();
   }
}

bool hh::PSX_File::try_resrt_flag_open(const int &new_flag)
{
    return (fcntl( _file_descriptor, F_SETFL, new_flag) != -1);
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
