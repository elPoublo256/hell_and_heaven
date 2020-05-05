#include "psx_files.h"
#include <iostream>
#include "../hh_exceptions/hh_exceptions.h"


hh::psx_file::PSX_File::PSX_File(const std::string &file_name, open_flag_t openflag)
{
  errno = 0;
  this->_file_descriptor = open(file_name.c_str(), openflag);
  if(_file_descriptor < 0)
  {
      if(errno != 0)
      {
          throw(hh::ErrnoException());
      }
      __filename = file_name;
  }
}

hh::psx_file::PSX_File::PSX_File(const std::string &file_name, open_flag_t openflag, permiss_t permiss)
{

    errno = 0;
    this->_file_descriptor = open(file_name.c_str(), openflag, permiss);
    if(_file_descriptor < 0)
    {
        if(errno != 0)
        {
            throw(hh::ErrnoException());
        }

    }
    __filename = file_name;
}

void hh:: psx_file::PSX_File::psx_close()
{
    errno = 0;
    close(_file_descriptor);
    if(errno != 0)
    {
        throw (hh::ErrnoException());
    }
}

void hh:: psx_file::PSX_File::_lseek(lseek_t flag, const long num_bytes)
{
    auto new_pos = lseek(_file_descriptor,num_bytes, flag);
    _curent_position = lseek(_file_descriptor, 0, SEEK_CUR);

}
void hh:: psx_file::PSX_File::lseek_from_begin(const long &num_bytes)
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

void hh:: psx_file::PSX_File::lseek_from_qurent(const long &num_bytes)
{
  _lseek(SEEK_CUR, num_bytes);
}

void hh:: psx_file::PSX_File::lseek_from_end(const long &num_bytes)
{
 _lseek(SEEK_END, num_bytes);
}

void hh:: psx_file::PSX_File::psx_read(void *dest, const long num_bytes)
{
    auto res = read(_file_descriptor,dest,num_bytes);
    if(res < 0)
    {
        throw hh::ErrnoException();
    }
    _curent_position += num_bytes;
}

void hh:: psx_file::PSX_File::psx_write(void *dest, const long num_bytes)
{

    auto res = write(_file_descriptor,dest,num_bytes);
    if(res < 0)
    {
        throw hh::ErrnoException();
    }
    _curent_position += num_bytes;
}

void hh:: psx_file::PSX_File::psx_defragment_read(const iovec *iov, int count_iov)
{
    auto res = readv(_file_descriptor, iov, count_iov);
    if(res == -1)
    {
        throw hh::ErrnoException();
    }
    for(int i = 0;  i <count_iov; i++)
    {
        _curent_position += iov->iov_len;
    }
}

void hh::psx_file::PSX_File::psx_defragment_write(const iovec *iov, int count_iov)
{
    auto res = writev(_file_descriptor,iov, count_iov);
    if(res < 0)
    {
        throw hh::ErrnoException();
    }
}
hh::psx_file::PSX_File::~PSX_File()
{

}

void hh::psx_file::PSX_File::reset_flag_open(const int &new_flag)
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

bool hh:: psx_file::PSX_File::try_resrt_flag_open(const int &new_flag) noexcept
{
    return (fcntl( _file_descriptor, F_SETFL, new_flag) != -1);
}

hh::psx_file::PSX_File&& hh::psx_file::PSX_File::make_duplicate()
{

    PSX_File duplcate;
    duplcate._file_descriptor = dup(_file_descriptor);
    duplcate._curent_position = _curent_position;
    duplcate._open_flag = _open_flag;
    return(std::move(duplcate));
}

void hh::psx_file::PSX_File::data_fsink()
{
    if(fdatasync(_file_descriptor) != 0)
    {
        throw hh::ErrnoException();
    }
}

void hh::psx_file::copy_psx_file(const PSX_File &original, const PSX_File &copy, std::size_t size_bufer)
{
    if(size_bufer != 0)
    {
    auto bufer = malloc(size_bufer);

    while (auto sreaded = read(original._file_descriptor, bufer, size_bufer) > 0)
    {
     if(write(copy._file_descriptor, bufer, sreaded) == sreaded)
     {
         throw hh::psx_file::PSX_Fiel_Exc(std::string("fail copy file"));
     }
    }
    free(bufer);
    return;
    }
    else {
        throw hh::psx_file::PSX_Fiel_Exc(std::string("Zero size bufer"));
    }
}

hh::psx_file::PSX_Temprorary_File::PSX_Temprorary_File(std::string teplate_fn)
{
    teplate_fn = teplate_fn + std::string("XXXXXX");
    _file_descriptor = mkstemp(const_cast<char*>(teplate_fn.data()));
    _filename = teplate_fn;
    _open_flag = O_EXCL;
}

hh::psx_file::PSX_Temprorary_File::~PSX_Temprorary_File()
{
    unlink(_filename.data());
}



