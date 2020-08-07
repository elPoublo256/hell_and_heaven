#include "../core_syslog/psx_syslog.h"
int main()
{
    hh::core_syslog::PSX_SysLOgger<LOG_INFO>* l =
            new hh::core_syslog::PSX_SysLOgger<LOG_INFO>("qwerty", LOG_PID);
    *l << "asdfg";
    delete l;
}
