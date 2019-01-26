#pragma once
#include "prosess.h"
#include "../core_files/file_stream.h"
#include "../hh_exceptions/hh_exceptions.h"
#include <memory>
namespace hh {

class PipeProcessBase;
class ReadPipeProcess;
class WritePipeProcess;

class PipeProcessBase : public hh::Fork_Process
{
  public:
    friend void connect(const ReadPipeProcess& reader, const WritePipeProcess& writer);
  protected:
    PipeProcessBase(std::shared_ptr<Base_Process> parent = get_main_ptr());
protected:
      mutable int _pipe_fd = -1;
      mutable int no_its_pipe_fd;

};

void connect(const ReadPipeProcess& reader, const WritePipeProcess& writer);

class ReadPipeProcess : public hh::PipeProcessBase
{
 public:
    ReadPipeProcess(std::shared_ptr<Base_Process> parent = get_main_ptr());
    virtual void start(const Exe_arg &arg) override;
protected:
    std::shared_ptr<hh::Base_IFile_Stream> pipe_read;

};

class WritePipeProcess : public hh::PipeProcessBase
{
public:
    WritePipeProcess(std::shared_ptr<Base_Process> parent = get_main_ptr());
    virtual void start(const Exe_arg &arg) override;
protected:
    std::shared_ptr<hh::Base_OFile_Stream> pipe_write;

};






}

