#include "pipe_process.h"
using namespace hell_and_haven::process_core;

NoNamePipeProcess::NoNamePipeProcess(std::shared_ptr<Base_Process> parent) : Fork_Process(parent)
{

}

NoNamePipeProcess::NoNamePipeProcess(std::shared_ptr<NoNamePipeProcess> &parent_writer)
{

}
