#ifndef PSX_BASE_FILE_H
#define PSX_BASE_FILE_H
#include "psx_base_buffer.h"
#include "../hh_exceptions/hh_exceptions.h"
#include <memory>
namespace hh {


template <class FD = int>
class BaseFD
{
public:
    BaseFD(){}
    BaseFD(const FD&){}
    virtual void copy(const FD& copy_fd) {__fd = copy_fd;}
    FD get_file_discriptror() const {return __fd;}
protected:
    FD __fd;

};

class BaseErrorFile{};

class BaseReader
{
public:
    BaseReader(){}
    virtual int psx_read(void* dest, const std::size_t &len){}
     hh::PSX_Base_Bufer&& psx_read(const std::size_t& len);
};

class BaseWriter
{
public:
    BaseWriter(){}
    virtual int psx_write(const void* src, const std::size_t& len){}
    std::size_t psx_write(const hh::PSX_Base_Bufer& buf);

};

class BaseReadWrite : public BaseReader, BaseWriter{};



template <typename FD>
class BaseOpen : public BaseFD<FD>
{
public:
    BaseOpen(const BaseFD<FD>& fd){this->__fd = fd.get_file_discriptror();}
    BaseOpen(const BaseOpen& copy) = delete;
    BaseOpen(BaseOpen&& rv){this->__fd = rv.__fd;}
    BaseOpen(){}
    //BaseOpen(const char* name, int open_flag){this->__fd = this->psx_open(name,open_flag);}
    virtual ~BaseOpen(){}
    //virtual FD psx_open(const char* name, int open_flag){}
    virtual void psx_close() = 0;
protected:


};

typedef std::shared_ptr<BaseWriter> write_f_ptr;
/// Abstract fubric of readers
class FubricWriteFiles
{
public:
    FubricWriteFiles(){}
    virtual ~FubricWriteFiles(){}

    virtual write_f_ptr get_write() = 0;
};
typedef std::shared_ptr<BaseReader> read_f_ptr;
/// Abstract fubric of writers
class FubricReadFiles
{
public:
    FubricReadFiles(){}
    virtual ~FubricReadFiles(){}

    virtual read_f_ptr get_read() = 0;

    };


typedef std::shared_ptr<BaseReadWrite> rdwr_f_ptr;



/// Abstract fubric of readwriters
class FubricReadWriteFiles : public FubricReadFiles, FubricWriteFiles
{
public:
    FubricReadWriteFiles() : FubricReadFiles(), FubricWriteFiles(){}
    virtual ~FubricReadWriteFiles(){}
    virtual rdwr_f_ptr get_readwrite() = 0;


};


class Base_FD_Open : public BaseOpen<int>
{
public:
    Base_FD_Open(){}
    Base_FD_Open(const int& fd) : BaseOpen<int>(fd){}
    Base_FD_Open(const Base_FD_Open& copy) = delete;
    Base_FD_Open(Base_FD_Open&& rv) : BaseOpen<int>(std::move(rv)){}
    virtual void psx_close();
    virtual ~Base_FD_Open(){psx_close();}
};

class BaseFDErrorFile : public BaseErrorFile, public hh::ErrnoException
{
  public:
    BaseFDErrorFile(const char* what) :
        hh::ErrnoException(what){}

};

class BaseFDReader : public Base_FD_Open, public BaseReader
{
public:
    BaseFDReader(){}
    BaseFDReader(const int& fd) : Base_FD_Open(fd){}
    BaseFDReader(BaseFDReader&& rv) : Base_FD_Open(std::move(rv)){}
    BaseFDReader(const BaseFDReader& copy) = delete;
    virtual int psx_read(void *dest, const std::size_t &len) override;
    PSX_Base_Bufer&& psx_read(const std::size_t& len) {return std::move(BaseReader::psx_read(len));}
};

class BaseFDWriter : public Base_FD_Open, public BaseWriter
{
public:
    BaseFDWriter(){}
    BaseFDWriter(const int& fd) : Base_FD_Open(fd){}
    BaseFDWriter(BaseFDWriter&& rv) : Base_FD_Open(std::move(rv)){}
    BaseFDWriter(const BaseFDWriter& copy) = delete;

    virtual int psx_write(const void *src, const std::size_t &len);
};


class BaseFDReaderWriter : public Base_FD_Open, public BaseReadWrite
{
public:
    BaseFDReaderWriter(){}
    BaseFDReaderWriter(const int& fd) : Base_FD_Open(fd){}
    BaseFDReaderWriter(BaseFDWriter&& rv) : Base_FD_Open(std::move(rv)){}
    BaseFDReaderWriter(const BaseFDWriter& copy) = delete;

     virtual int psx_write(const void *src, const std::size_t &len);
     virtual int psx_read(void *dest, const std::size_t &len);


};



}
#endif // PSX_BASE_FILE_H
