#pragma once
#include <string>
#include <pwd.h>
#include <grp.h>
#include <exception>
#include <list>
namespace hh 
{
namespace core_user
{
	class Group
	{
		private:


            group* __group_ptr;
            static void load_group_file();
            bool __is_valid;
		public:

			Group(const std::string& group_name);
            Group(const int& gid);
            Group(Group&& rv_gr) = default;
            Group(const Group& copy) = default;
            Group operator = (Group&& rv_gr);
            Group operator = (const Group& copy);
            inline bool operator == (const Group& other)
            {return __group_ptr->gr_gid == other.__group_ptr->gr_gid;}

			bool operator == (const std::string group_name);
            inline bool is_valid() {return __is_valid;}

            inline auto get_group_name() {return std::string(__group_ptr->gr_name);}
            std::list<std::string> get_members_names_list();
            inline auto get_gid(){return __group_ptr->gr_gid;}
            inline auto get_passward(){return std::string(__group_ptr->gr_passwd);}

			

    };
}
}
