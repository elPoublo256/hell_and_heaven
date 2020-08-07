#pragma once
#include <paths.h>
#include <utmpx.h>
#include <string>
#include <string.h>
#include <unistd.h>
#include <stdexcept>
#include <memory>
namespace hh {
namespace core_user {

//TODO typdef ....

inline auto get_file_path_curent_users_logeted() noexcept {return _PATH_UTMP;}
inline auto get_file_path_fullhisoty_users_logeted() noexcept {return _PATH_WTMP;}

class PSX_Login_Error : public std::runtime_error
{
public:
    PSX_Login_Error(const std::string& er) :
        std::runtime_error(er) {}
};

class PSX_Login_Info : public utmpx //every fild-end = NULL
{
public:

    PSX_Login_Info(const int& type = USER_PROCESS);
    PSX_Login_Info(const utmpx *ptr);
    ///constructor for searching in file
    PSX_Login_Info(const int& type,
                   const char* line_c_str);
    PSX_Login_Info(const PSX_Login_Info& copy) : utmpx(copy){}
    PSX_Login_Info(PSX_Login_Info&& rv_c) : utmpx(rv_c){}
    auto get_type() const {return this->ut_type;}
    auto get_line() const {return this->ut_line;}
    auto get_session_id() const {return ut_session;}
    auto get_pid() const {return ut_pid;}

    std::string get_host() const;



};


/*!
 * \brief get_next_log_info - return logical_and
 * \throw PSX_Login_Error("getutxent return NULL")
 * \return
 */
PSX_Login_Info&& get_next_log_info();
//TODO using getutx(id,type,line ....)
PSX_Login_Info&& get_find_with_type(const int& type); //TODO
PSX_Login_Info&& get_find_with_line(const std::string& line);

typedef std::shared_ptr<PSX_Login_Info> PSX_Login_Info_ptr;
//TODO noexcept geters return shared_ptr



//use utmpxname
void set_infofile(const std::string& filename) noexcept;

inline auto get_curent_user_login(){
return std::string(getlogin());}
}
}
