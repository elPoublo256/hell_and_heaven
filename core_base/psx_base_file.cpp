#include "psx_base_file.h"
#include <unistd.h>
hh::PSX_Base_Bufer&& hh::BaseReader::psx_read(const std::size_t& len)
{
    PSX_Base_Bufer res(len);
    auto size = this->psx_read(res.get_ptr(),len);


    res.resize(len);
    return std::move(res);
}

std::size_t hh::BaseWriter::psx_write(const hh::PSX_Base_Bufer &buf)
{
    auto r = this->psx_write(buf.get(),buf.size_in_bytes());

}


void hh::Base_FD_Open::psx_close()
{
    close(__fd);
}

int hh::BaseFDReader::psx_read(void *dest, const std::size_t &len)
{
    int res = read(__fd,dest,len);
    if(res < 0)
    {
        throw hh::BaseFDErrorFile("error read");
    }
    return res;
}

int hh::BaseFDWriter::psx_write(const void *src, const std::size_t &len)
{
   int res = write(__fd, src, len);
   if(res < 0)
   {
       throw hh::BaseFDErrorFile("error write");
   }
   return res;

}


int hh::BaseFDReaderWriter::psx_read(void *dest, const std::size_t &len)
{
    int res = read(__fd,dest,len);
    if(res < 0)
    {
        throw hh::BaseFDErrorFile("error read");
    }
    return res;
}

int hh::BaseFDReaderWriter::psx_write(const void *src, const std::size_t &len)
{
   int res = write(__fd, src, len);
   if(res < 0)
   {
       throw hh::BaseFDErrorFile("error write");
   }
   return res;
}
