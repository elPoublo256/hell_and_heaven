#include "psx2_signal_info.h"
using namespace hh::core_process;




PSX2_BaseSignalHandler::PSX2_BaseSignalHandler(void (*info_handler)
                                               (int, const SignalInfo &,
                                                const UserContext &),
                                               int flag,
                                               const SetSignals &s)

{

}


#if defined __USE_POSIX199309 || defined __USE_XOPEN_EXTENDED
INITT_STATIC_OWNER(hh::core_process::InfoVirtualSignalHandler);

hh::core_process::InfoVirtualSignalHandler::
InfoVirtualSignalHandler(const int &flag, const SetSignals &set)

{
    set_owner(this);
    //StatFunct::action()
}
#endif

