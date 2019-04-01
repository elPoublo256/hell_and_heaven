#pragma once
#include <pwd.h>
#include <string>
namespace hh
{
namespace user
{
 class User
 {
 private:
     passwd* __pwd;
     bool __is_valid;
 public:
     User(const std::string& user_name);
     User(const int& user_id);
     User(const User& copy) = default;
     User(User&& rv_copy) = default;
     User operator = (const User& copy);
     User operator = (User&& rv_copy);



 };
}
}
