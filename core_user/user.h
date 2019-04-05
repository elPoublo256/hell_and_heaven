#pragma once
#include <pwd.h>
#include <string>
namespace hh
{
namespace userspace
{
 class User
 {
 private:
     passwd* __pwd;
     bool __is_valid;
 public:
     //! last char should be '\0'
     User(const std::string& user_name);
     User(const int& user_id);
     User(const User& copy) = default;
     User(User&& rv_copy) = default;
     User operator = (const User& copy);
     User operator = (User&& rv_copy);
     friend bool check_passward(const User& user, std::string&& passwd);



 };
 bool check_passward(const User& user, std::string&& passwd);

}
}
