#include "file_stream.h"
Base_IFile_Stream::Base_IFile_Stream(const int& file_descriptor,
                                     const int& pos)
{
    set_filedcripter(file_descriptor);
    lseek(file_descriptor, pos, SEEK_SET);
}

Base_IFile_Stream::Base_IFile_Stream(const std::string &file_name)
{
  set_filedcripter(open(file_name.c_str(), O_RDONLY));

}


Base_IFile_Stream::Base_IFile_Stream(const char *c_name)
{
    set_filedcripter(open(c_name, O_RDONLY));
}
Base_OFile_Stream::Base_OFile_Stream(int file_descriptor)
{
    set_filedcripter( file_descriptor);
}

Base_OFile_Stream::Base_OFile_Stream( std::string &file_name, int flag)
{
  set_filedcripter(open(file_name.c_str(), O_RDWR|O_CREAT | flag , S_IRWXU));
}

Base_OFile_Stream::Base_OFile_Stream(std::string && file_name, int flag)
{
    std::string s = std::move(file_name);
    set_filedcripter(open(s.c_str(), O_RDWR | O_CREAT | flag, S_IRWXU ));
}


