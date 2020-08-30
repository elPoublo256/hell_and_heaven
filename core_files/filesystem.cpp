#include "filesystem.h"
#include "../hh_exceptions/hh_exceptions.h"

hh::filesystem::FileSystemInfo::FileSystemInfo(const int &file_discripotr)
{
 if(fstatvfs(file_discripotr, this) == -1)
 {
     throw hh::ErrnoException();
 }
}
hh::filesystem::FileSystemInfo::FileSystemInfo(const hh::core_files::Base_FS_File &Base_FS_File)
{
    if(fstatvfs(Base_FS_File.get_file_discriptror(), this) == -1)
    {
        throw hh::ErrnoException();
    }
}
hh::filesystem::FileSystemInfo::FileSystemInfo(const hh::core_files::PSX_Directory &psx_dir)
{
    if(fstatvfs(psx_dir.get_file_discriptror(), this) == -1)
    {
        throw hh::ErrnoException();
    }
}

hh::filesystem::FileSystemInfo::FileSystemInfo(const std::string &path)
{
    //TODO
    //i get undefined reference to statvfs::statvfs(char*, statvfs*)
    //hh::core_files::Base_FS_File f(path);
    //fstatvfs(f.get_file_discriptror(), this);

}

hh::filesystem::FileAtributInfo::FileAtributInfo(const int &file_discripotr)
{
    if(fstat(file_discripotr,this) == -1)
    {
        throw hh::ErrnoException();
    }
}
hh::filesystem::FileAtributInfo::FileAtributInfo(const std::string &path)
{
    if(lstat(path.c_str(),this)== -1)
    {
        throw hh::ErrnoException();
    }
}

hh::filesystem::FileAtributInfo::FileAtributInfo(const hh::core_files::Base_FS_File &file)
{
    if(fstat(file.get_file_discriptror(),this) == -1)
    {
        throw hh::ErrnoException();
    }
}

void hh::filesystem::reset_atribut_time(const std::string filename, const utimbuf &times)
{
    auto copy = times;
    if(utime(filename.c_str(), &copy) == -1)
    {
        throw hh::ErrnoException();
    }
}

void hh::filesystem::set_owner(const int &fd, const uid_t &user_id, const gid_t &group_id)
{
    if(fchown(fd,user_id,group_id));
}

void hh::filesystem::change_mode(const int &fd, const __mode_t& mode)
{
    if(fchmod(fd, mode) == -1)
    {
        throw ErrnoException();
    }
}

