#include "file_stream.h"
#include <libgen.h>

using namespace hell_and_haven;
void OpenFileError::set_error_what(const decltype(errno) &error_erno)
{
    switch (error_erno) {
    case EEXIST:
        err_what =std::string("O_CREAT and O_EXCL are set, and the named file exists.");
        break;
    case EACCES:
        err_what = std::string("Search permission")
                               +std::string(" is denied on a component of")
                                +std::string(" the path prefix, or the file")
                                 +std::string(" exists and the permissions ")
                                  +std::string("specified by oflag are denied,")
                                   +std::string(" or the file does not exist ")
                                    +std::string("and write permission is")
                                     +std::string(" denied for the parent")
                                      +std::string(" directory of the file to be")
                                      +std::string(" created, or O_TRUNC is specified")
                                       +std::string(" and write permission is denied.");
      break;
    case EINTR:
        err_what = std::string("A signal was caught during open().");
        break;
    case EINVAL:
        err_what = std::string("The implementation does not support synchronized I/O")
                               +std::string(" for this file.");
        break;
    case EIO:
        err_what = std::string("The path argument names a STREAMS file and a hangup")
                               +std::string(" or error occurred during the open().");
        break;
    case EISDIR:
        err_what = std::string("The named file is a directory and ")
                               +std::string("oflag includes O_WRONLY or O_RDWR.");
        break;
    case ELOOP:
        err_what = std::string("A loop exists in symbolic links encountered during")
                               +std::string(" resolution of the path argument.");
        break;
    case EMFILE:
        err_what = std::string("{OPEN_MAX} file descriptors are currently open")
                               +std::string(" in the calling process.");
        break;
    case ENAMETOOLONG:
        err_what = std::string("The length of the path argument exceeds {PATH_MAX} or")
                   +std::string(" a pathname component is longer than {NAME_MAX}");
        break;
    case ENFILE:
        err_what = std::string("The maximum allowable number of files ")
                               +std::string("is currently open in the system.");
        break;
    case ENOENT:
        err_what = std::string("O_CREAT is not set and the named file does not exist;")
                    +std::string(" or O_CREAT is set and either the path prefix does")
                     +std::string(" not exist or the path argument points to an")
                     +std::string(" empty string.");
        break;
    case ENOSR:
        err_what = std::string("The path argument names a STREAMS-based file ")
                        +std::string("and the system is unable to allocate a STREAM.");
        break;
    case ENOSPC:
        err_what = std::string("The directory or file system that would contain")
                               +std::string(" the new file cannot be expanded,")
                               +std::string(" the file does not exist, and O_CREAT is specified");
        break;
    case ENOTDIR:
        err_what = std::string("A component of the path prefix is not a directory.");
        break;
    case ENXIO:
        err_what = std::string("O_NONBLOCK is set, the named file is a FIFO, O_WRONLY")
                   +std::string(" is set, and no process has the file open for reading.");
        break;
    case EOVERFLOW:
        err_what = std::string("The named file is a regular file and the size of the file")
                    +std::string(" cannot be represented correctly in an object of type off_t.");
        break;
    case EROFS:
        err_what = std::string("The named file resides on a read-only file system ")
                               +std::string("and either O_WRONLY, O_RDWR, O_CREAT ")
                                +std::string("(if the file does not exist), or O_TRUNC is set in")
                                 +std::string(" the oflag argument.");
        break;
    case EAGAIN:
        err_what = std::string("The path argument names the slave side of a pseudo-terminal")
                               +std::string(" device that is locked");
        break;
    default:
        break;
    }


}

OpenFileError::OpenFileError(const decltype(errno) &error_erno)
{
    error_open = error_erno;
    set_error_what(error_open);
}

OpenFileError::OpenFileError(const int &&error_erno)
{
    error_open = std::move(error_erno);
    set_error_what(error_open);

}

void PSX_File::set_filedcripter(const int& fdr)
{
    if(fdr == -1)
    {
        throw OpenFileError(errno);
    }
    _file_descriptor = fdr;
}

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


