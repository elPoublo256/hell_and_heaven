#pragma once
#include <syslog.h>
#include <string>
#include <sstream>
namespace hh {
namespace core_syslog {

template<int level>
class PSX_SysLOgger
{
public:
    /*!
     * \brief PSX_SysLOgger - constructor
     * \param ident - string in each system message
     * \param option - options like LOG_CONS, ...
     * \param facility -
     */
    PSX_SysLOgger(const std::string& ident,
                  const int& option,
                  const int& facility = LOG_USER
                  )
    {
        openlog(ident.c_str(), option, facility);
    }

    template <class T>
    PSX_SysLOgger& operator << (const T& mess_part)
    {
        log_stream << mess_part;
        return *this;
    }

    ~PSX_SysLOgger()
    {
        syslog(prioriti, log_stream.str().c_str());
    }

private:
    std::stringstream log_stream;
    int prioriti;


};

}

}
