#pragma once
#include <string>
#include <list>
#include <sys/statvfs.h>
#include <dirent.h>
#include "psx_files.h"
namespace hh {
namespace psx_file {



class PSX_Directory : public BasePSXFile
{
public:
    PSX_Directory(const std::string& file_name, open_flag_t openflag = O_RDONLY);

    /// cd (new_path)
    void change_dir (const std::string& dir_name);
    //TODO std::list<std::string> list_filenames() const;
    void add_child_dir(const std::string& dirname, const permiss_t& mod) const;
    //void remove_dir(const std::string& dirname) const;
    friend class FileSystem;
    std::string get_name(){return _dir_name;}
    //PSX_File&& create_file(const std::string filename);

protected:
    std::string _dir_name;

    open_flag_t __flag;


};



}

}
