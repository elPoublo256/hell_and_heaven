#pragma once
#include <string>
#include <list>
#include <sys/statvfs.h>
#include "psx_files.h"
namespace hh {
namespace psx_file {



class PSX_Directory : public BasePSXFile
{
public:
    PSX_Directory(const std::string& dir_name);

    /// cd (new_path)
    void change_dir (const std::string& dir_name);
    void change_dir(const PSX_Directory& other);
    std::list<PSX_File> list_fiales() const;
    std::list<std::string> list_filenames() const;
    std::list<PSX_Directory> list_dirs() const;
    void add_child_dir(const std::string& dirname) const;
    void remove_dir(const std::string& dirname) const;
    friend class FileSystem;

    //PSX_File&& create_file(const std::string filename);

protected:
    std::string _dir_name;


};

}

}
