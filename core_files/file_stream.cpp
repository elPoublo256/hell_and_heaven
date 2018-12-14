#include "file_stream.h"


PSX_File::OpenFileError::OpenFileError(decltype(errno) error_erno)
{
    std::string err_what;
    error_open = error_erno;
    switch (error_erno) {
    case EEXIST:
        err_what =std::string("O_CREAT and O_EXCL are set, and the named file exists.");
        break;
    case EACCES:
        err_what = std::string("Search permission"
                               +" is denied on a component of"
                                +" the path prefix, or the file"
                                 +" exists and the permissions "
                                  +"specified by oflag are denied,"
                                   +" or the file does not exist "
                                    +"and write permission is"
                                     +" denied for the parent"
                                      +" directory of the file to be"
                                      +" created, or O_TRUNC is specified"
                                       +" and write permission is denied.");
      break;
    case EINTR:
        err_what = std::string("A signal was caught during open().");
        break;
    case EINVAL:
        err_what = std::string("The implementation does not support synchronized I/O"
                               +" for this file.");
        break;
    case EIO:
        err_what = std::string("The path argument names a STREAMS file and a hangup"
                               +" or error occurred during the open().");
        break;
    case EISDIR:
        err_what = std::string("The named file is a directory and "
                               +"oflag includes O_WRONLY or O_RDWR.");
        break;
    case ELOOP:
        err_what = std::string("A loop exists in symbolic links encountered during"
                               +" resolution of the path argument.");
        break;
    case EMFILE:
        err_what = std::string("{OPEN_MAX} file descriptors are currently open"
                               +" in the calling process.");
        break;
    case ENAMETOOLONG:
        err_what = std::string("The length of the path argument exceeds {PATH_MAX} or"
                               +" a pathname component is longer than {NAME_MAX}");
        break;
    case ENFILE:
        err_what = std::string("The maximum allowable number of files "
                               +"is currently open in the system.");
        break;
    case ENOENT:
        err_what = std::string("O_CREAT is not set and the named file does not exist;"
                               +" or O_CREAT is set and either the path prefix does"
                                +" not exist or the path argument points to an"
                                 +" empty string.");
        break;
    case ENOSR:
        err_what = std::string("The path argument names a STREAMS-based file "
                               +"and the system is unable to allocate a STREAM.");
        break;
    case ENOSPC:
        err_what = std::string("The directory or file system that would contain"
                               +" the new file cannot be expanded,"
                               +" the file does not exist, and O_CREAT is specified");
        break;
    case ENOTDIR:
        err_what = std::string("A component of the path prefix is not a directory.");
        break;
    case ENXIO:
        err_what = std::string("O_NONBLOCK is set, the named file is a FIFO, O_WRONLY"
                               +" is set, and no process has the file open for reading.");
        break;
    case EOVERFLOW:
        err_what = std::string("The named file is a regular file and the size of the file"
                               +" cannot be represented correctly in an object of type off_t.");
        break;
    case EROFS:
        err_what = std::string("The named file resides on a read-only file system "
                               +"and either O_WRONLY, O_RDWR, O_CREAT "
                                +"(if the file does not exist), or O_TRUNC is set in"
                                 +" the oflag argument.");
        break;
    case EAGAIN:
        err_what = std::string("The path argument names the slave side of a pseudo-terminal"
                               +" device that is locked");
        break;
    case EINVAL:
        err_what = std::string("The value of the oflag argument is not valid.");
        break;

    default:
        break;
    }
}

void PSX_File::set_filedcripter(const int& fdr)
{
    if(fdr == -1)
    {
        throw PSX_File::OpenFileError(errno);
    }
    fd = fdr;
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


