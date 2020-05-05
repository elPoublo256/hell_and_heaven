#include "accouting_process.h"
using namespace hh::process;

AccoutingInfoFile* AccoutingInfoFile::_active = nullptr;
/* TODO
AccoutingInfoFile::AccoutingInfoFile(const hh::psx_file::PSX_File &&psx_file) :
    hh::psx_file::PSX_File(std::move(psx_file))
{

}
*/
AccoutingInfoFile::AccoutingInfoFile(const std::__cxx11::string &file_name)
{
  this->__filename = file_name;
}

void AccoutingInfoFile::read_accouting_inf(struct acct &c_info)
{
    this->psx_read(&c_info,sizeof(struct acct));
}

void AccoutingInfoFile::read_accouting_inf(AccoutingInfo &info)
{
    this->psx_read(&info,sizeof(struct acct));
}

void AccoutingInfoFile::psx_open()
{
    this->_file_descriptor = open(__filename.c_str(), O_RDONLY);
    if(_file_descriptor < 0)
    {
        if(errno != 0)
        {
            throw AccoutingInfoError("error opening file");
        }

    }

}


void AccoutingInfoFile::set_as_accFile() const
{
    if(_active)
    {
        throw AccoutingInfoError("allredy active some acct");
    }
    acct(__filename.c_str());
}

const AccoutingInfoFile* AccoutingInfoFile::get_qurent_active_file()
{
    return AccoutingInfoFile::_active;
}

void AccoutingInfoFile::off_accouting()
{
    acct(NULL);
}
