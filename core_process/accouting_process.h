#pragma once
#include <sys/acct.h>
#include "../core_files/psx_files.h"
#include <functional>
#include <memory>
namespace hh {
namespace process {


struct AccoutingInfo : public acct
{

};

class AccoutingInfoError : public std::runtime_error
{
public:
    AccoutingInfoError(const std::string& err) : std::runtime_error(err){}

};


class AccoutingInfoFile : public hh::core_files::Base_FS_File
{
public:
    /*!
     * \brief AccoutingInfoFile
     * move-constructor from opened PSX-File
     * you should not use this constructor
     * \param psx_file - r-value reference to PSX-File
     */
   //TODO AccoutingInfoFile(const hh::psx_file::PSX_File&& psx_file);
    /*!
     * \brief AccoutingInfoFile
     * Create object, but not file in file-system
     * filename vill used in acct() when you emit method for ON accouting
     * \param file_name
     */
    AccoutingInfoFile(const std::string& file_name);
    /*!
     * \brief read_accouting_inf read info from file
     * if file is not opened, realisation this method open file
     * with flag O_RDONLY
     * \param c_info
     */
    void read_accouting_inf(struct acct& c_info);

    /*!
     * \brief read_accouting_inf  read info from file
     * if file is not opened, realisation this method open file
     * with flag O_RDONLY
     * \param info
     */
    void read_accouting_inf(AccoutingInfo& info);

    /*!
     * \brief open - open file with name seted in constructor with name
     * with flog O_RDONLY
     */
    void psx_open();

    /*!
     * \brief set_as_accFile
     * ON accouting using acct() with curent filename
     * if accouting allredy - throw AccoutingInfoError
     * \throw  AccoutingInfoError
     */
    void set_as_accFile() const;

    static void off_accouting();

    static const AccoutingInfoFile* get_qurent_active_file();
protected:

    static AccoutingInfoFile* _active;


};


}

}
