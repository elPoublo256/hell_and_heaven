#include "psx_base_file.h"
#include <unistd.h>
#include <sstream>
hh::PSX_Base_Bufer hh::BaseReader::psx_read(const std::size_t& len)
{

    void* buf = malloc(len);

    std::size_t s = (std::size_t) this->psx_read(buf,len);
    ;
    return PSX_Base_Bufer(s,buf);// std::move(res);




}

std::size_t hh::BaseWriter::psx_write(const hh::PSX_Base_Bufer &buf)
{
    auto r = this->psx_write(buf.get(),buf.size_in_bytes());

}


void hh::Base_FD_Open::psx_close()
{
    close(__fd);
}

std::size_t hh::BaseFDReader::psx_read(void *dest, const std::size_t &len)
{

    int res = read(__fd,dest,len);
    if(res < 0)
    {
     std::stringstream ss;
     ss<<"error read from fd="<<__fd;
        throw hh::BaseFDErrorFile(ss.str().c_str());
    }
    return std::size_t(res);
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



std::size_t hh::BaseFDReaderWriter::psx_read(void *dest, const std::size_t &len)
{
    int res = read(__fd,dest,len);
    if(res < 0)
    {
        throw hh::BaseFDErrorFile("error read");
    }
    return std::size_t(res);
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
