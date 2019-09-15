#pragma once
#include<map>
#include <unistd.h>
#include <vector>
#include <string>
#include <functional>
#include <iostream>
#include <iterator>
#include <cstdarg>
#include <string.h>
#include <memory>
#include <signal.h>
#include <unordered_map>
#include "../core_files/file_stream.h"
#include <list>
#include <iostream>
#include "exe_arg.h"
#include <array>
namespace hh {

namespace process {
/*!
 * \brief The Base_Process class
 * This class provide parent of all Processes-classes
 *
 */
class Base_Process
{
  public:

    struct Process_ID
    {
        int pocess_id;
        int group_id_real, group_id_effect;
        int user_id_real, user_id_effect;
#ifdef __linux__
        int group_id_saved, user_id_saved;
#endif
    };

    Base_Process();
    virtual ~Base_Process();

    typedef std::map<std::string,std::string>::iterator envir_iter_t;
    typedef std::map<std::string,std::string>::const_iterator c_envir_iter_t;

    virtual void start(hh::Exe_arg &arg);

    /*!
     * \brief susv3_get_environ
     * \param key - name of parameter
     * \return string with value of parameter in SUSv3-style
     */
    std::string&& susv3_get_environ(const std::string& key) const;//return "key=value"

    /*!
     * \brief get_environ
     * \param key - name of parameter
     * \return string with value of parameter in POSIX-style
     */
    std::string&& get_environ(const std::string& key) const;

    /*!
     * \brief set_environ - set new or overflow parameter in enviroments
     * \param key - name of parameter
     * \param value - new value of parameter
     * \param overflow - If name does exist
       in the environment, then its value is changed to value if overwrite
       is nonzero; if overwrite is zero, then the value of name is not
       changed
     */
    void set_environ(const std::string& key, const std::string& value,
                     const int& overflow = 0);


    /*!
     * \brief unset_environ - remove parameter in enviroments
     * \param key
     */
    void unset_environ(const std::string key);

    /*!
     * \brief clean_environ - remove all parameters of enviroments
     */
    void clean_environ();

    inline auto get_all_envir(){return std::pair<c_envir_iter_t,
                c_envir_iter_t>{__environ_map.begin(),__environ_map.end()};}

    ///if is_effectvie - return effectife Group ID, else real Group ID
    inline auto get_Group_id(const bool& is_effectvie = true) const
    {
        return is_effectvie ?  id.group_id_effect :  id.group_id_real;
    }

    ///if is_effectvie - return effectife Group ID, else real Group ID
    inline auto get_User_id(const bool& is_effectvie = true) const
    {
        return is_effectvie ?  id.user_id_effect :  id.user_id_real;
    }
#ifdef __linux__
    inline auto get_Group_id_saved(){return id.group_id_saved;}
    inline auto get_User_id_saved(){return id.user_id_saved;}
    void set_all_group_id(const int& r_gid,const int& e_gid, const int& s_gid);
    void set_all_user_id(const int& r_uid,const int& e_uid, const int& s_uid);
#endif

///set GID ore throw exception hh::PermissionErr
    void set_real_group_id(const int& new_gid);
    void set_effective_group_id(const int& new_gid);
///set UID ore throw exception hh::PermissionErr
    void set_real_user_id(const int& new_uid);
    void set_effective_user_id(const int& new_uid);

 protected:
    std::map<std::string,std::string> __environ_map;
    Process_ID id;



 protected:
    ///load IDs of curent process in Process_ID id using C-POSIX functions

    virtual void prepare_before_start();
    virtual void run(hh::Exe_arg &arg);
    virtual void load_all_id() noexcept;
    void load_map_environ() noexcept;
    virtual int main(int argv, char* argc[]) = 0;


};

}

}
