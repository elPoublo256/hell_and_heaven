#pragma once
#include <sys/time.h>
#include <string>
#include <functional>
#include "../locales/locales.h"
#include <time.h>
#include <sys/time.h>
namespace hh {
namespace core_info {
namespace clock_time {
struct Date
{
    uint32_t ear;
    uint8_t month;
    uint8_t day;


};

class DayTime
{
public:
    uint8_t hour;
    uint8_t mins;
    uint8_t seconds;
    uint16_t m_seconds;
    uint16_t mk_seconds;
};

class FullTime
{
private:
    union uDate{uint64_t __pedding; Date d;};
    union uTime{uint64_t __pedding; DayTime t;};
};struct Date
{
    uint32_t ear;
    uint8_t month;
    uint8_t day;


};

class DayTime
{
public:
    DayTime(){}
    DayTime(const tm& tm_time){}
    uint8_t hour;
    uint8_t mins;
    uint8_t seconds;
    uint16_t m_seconds;
    uint16_t mk_seconds;
};

class FullTime
{
private:
    union uDate{uint64_t __pedding; Date d;};
    union uTime{uint64_t __pedding; DayTime t;};
};
namespace GlobalSystemClock
{
    inline time_t get_C_time(){return time(NULL);}
    inline time_t get_C_time_from(const time_t& t){auto t2 = t; return time(&t2);}
    inline std::string get_string_C_date(const time_t& t){auto t2 = t; return std::string(ctime(&t2));}
    //TODO
    inline Date get_ToDay(){Date today; return today;}
    //TODO
    inline DayTime get_DayTime(){return DayTime();}



}







}

}

}
