#pragma once
#include "../../../core_files/psx_files.h"
#include "../../../hh_exceptions/hh_exceptions.h"
//#include "../psx_base_message_sequenc.h"
#include "../../../core_base/psx_base_file.h"
namespace hh {
namespace core_ipc {

class PipeError : hh::ErrnoException
{
public:
    PipeError() : hh::ErrnoException(){}
    PipeError(std::string&& err) : __err(err) {}

    const char* what() {return  std::string(__err +
                                      std::string(" : ")
                                      + std::string(hh::ErrnoException::what())).c_str();}
private:
    std::string __err;

};


/*!
 * \brief The ReadPipe class for reading from pipe
 */
class  ReadPipe : public BaseFD<int>, public BaseReader
{
public:
     ReadPipe(const int& fd_read);
     int psx_read(void *dest, const std::size_t &len);
     //ReadPipe(const int pair_fd[2]);


};

class WritePipe : public BaseFD<int>, public BaseWriter
{
public:
    WritePipe(const int& fd_wirite);
    int psx_write(const void *src, const std::size_t &len) override;
    //WritePipe(const int pair_fd[2]);
};

class Base_Pipe : public hh::FubricReadFiles, hh::FubricWriteFiles
{
public:

    Base_Pipe();
    bool is_opened_read();
    Base_Pipe(const Base_Pipe& copy) = delete;
    inline auto get_read_fd() const {return __pairpipe[0];}
    inline auto get_write_fd() const {return __pairpipe[1];}



#ifdef __USE_GNU
//    Base_Pipe(const int& flag);
#endif
private:
    //bool __is_opened_read;
    int __pairpipe[2];
};













}

}
