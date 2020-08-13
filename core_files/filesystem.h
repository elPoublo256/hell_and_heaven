#pragma once
#include <sys/statvfs.h>
#include <sys/stat.h>
#include <utime.h>
#include "../core_user/user.h"
#include "psx_directory.h"
namespace hh {
namespace filesystem {

class FileSystemInfo : public statvfs
{
public:
    FileSystemInfo(){}
    FileSystemInfo(const int& file_discripotr);
    FileSystemInfo(const std::string& path);
    FileSystemInfo(const hh::psx_file::PSX_File& psx_file);
    FileSystemInfo(const psx_file::PSX_Directory& psx_dir);
    std::size_t size_file_system_block(){return f_bsize;}
    std::size_t size_fundamental_block(){return f_frsize;}
    auto num_blocks_in_fylesystem(){return f_blocks;}
    auto num_free_blocks_in_fylesystem(){return f_bfree;}
    auto num_of_free_blocks_for_unprivileged_users()
    {
        return f_bavail;
    }
    auto num_indeks_discriptors(){return f_files;}
    auto num_free_indeks_discriptors(){return f_ffree;}
    auto num_free_indeks_discriptors_for_unprivileged_users()
    {return f_favail;}

    auto filesystem_id(){return f_fsid;}
    auto mount_flag(){return f_flag;}
    std::size_t max_length_filename()
    {return f_namemax;}


};

class FileAtributInfo : public stat
{
public:
    FileAtributInfo(){}
    FileAtributInfo(const int& file_discripotr);
    FileAtributInfo(const std::string& path);
    FileAtributInfo(const hh::psx_file::BasePSXFile& psx_file);
    //--------------------------------------
    //geting file_atribut
   inline auto get_device_id(){return st_dev;}
    inline auto get_indecs_discriptor(){return st_ino;}
    inline auto get_mode_file(){return st_mode;}
    ///num hard(soliod) reference to this file
    inline auto get_num_hard_link(){return st_nlink;}
    inline auto get_user_id(){return st_uid;}
    inline auto get_group_id(){return st_gid;}
    inline auto get_specific_devaice_id(){return st_rdev;}
    inline auto get_file_size(){return st_size;}
    inline auto get_blocksize_for_ffylesistem(){return st_blksize;}
    inline auto get_number_512B_blocks(){return st_blocks;}
    //TODO разобраться с типом
    inline auto get_time_last_acces(){return st_atime;}
    inline auto get_time_last_madification(){return st_mtime;}
    inline auto get_time_last_status_changed(){return st_ctim;}
    inline auto get_SUSv3_type_file(){return (st_mode & S_IFMT);}


};
//TODO сделать через файловый дискриптор и свои классы
void reset_atribut_time(const std::string filename,
                        const utimbuf& times);

void set_owner(const int& fd, const uid_t& user_id, const gid_t& group_id);

inline void set_owner(const hh::psx_file::BasePSXFile& file,
                                const uid_t& user_id,
                                const gid_t& group_id)
{
    set_owner(file.get_file_discriptror(), user_id, group_id);
}

inline void set_owner(const int& fd,const hh::core_user::User& user)
{
    set_owner(fd, user.get_user_id(), user.get_group_id());
}

inline void set_owner(const psx_file::BasePSXFile &file, const hh::core_user::User& user)
{
    set_owner(file, user.get_user_id(), user.get_group_id());
}


void change_mode(const int& fd, const __mode_t& mode);

void change_mode(const hh::psx_file::BasePSXFile& file, __mode_t);



}
}
