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
class  ReadPipe : public BaseFDReader
{
public:
    ReadPipe(const int& fd_read) : BaseFDReader(fd_read){}

};

class WritePipe : public BaseFDWriter
{
public:
    WritePipe(const int& fd_wr) : BaseFDWriter(fd_wr) {}
};



class Base_Pipe : public FubricReadFiles , public FubricWriteFiles
{
public:

    Base_Pipe();
    bool is_opened_read();
    Base_Pipe(const Base_Pipe& copy) = delete;
    inline auto get_read_fd() const {return __pairpipe[0];}
    inline auto get_write_fd() const {return __pairpipe[1];}
    virtual read_f_ptr get_read() {return __read_pipe_ptr;}
    virtual write_f_ptr get_write() {return __write_pipe_ptr;}



#ifdef __USE_GNU
//    Base_Pipe(const int& flag);
#endif
private:
    std::shared_ptr<ReadPipe> __read_pipe_ptr;
    std::shared_ptr<WritePipe>__write_pipe_ptr;

    //bool __is_opened_read;
    int __pairpipe[2];
};






}
}
