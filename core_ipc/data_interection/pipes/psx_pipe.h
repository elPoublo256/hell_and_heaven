#pragma once
#include "../../../core_files/psx_files.h"
#include "../../../hh_exceptions/hh_exceptions.h"
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

class Base_Pipe
{
public:

    Base_Pipe();
    bool is_opened_read();
    Base_Pipe(const Base_Pipe& copy) = delete;
    inline auto get_read_fd() const {return __fd[0];}
    inline auto get_write_fd() const {return __fd[1];}


#ifdef __USE_GNU
    Base_Pipe(const int& flag);
#endif
private:
    //bool __is_opened_read;
    int __fd[2];


};



/*!
 * \brief The ReadPipe class for reading from pipe
 */
class  ReadPipe : public hh::psx_file::BaseReadFile
{
public:
     ReadPipe(const Base_Pipe& piarpipe);
     //ReadPipe(const int pair_fd[2]);


};

class WritePipe : public hh::psx_file::BaseWriteFile
{
public:
    WritePipe(const Base_Pipe& piarpipe);
    //WritePipe(const int pair_fd[2]);
};

}

}
