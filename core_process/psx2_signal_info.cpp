#include "psx2_signal_info.h"

#if defined __USE_POSIX199309 || defined __USE_XOPEN_EXTENDED
INITT_STATIC_OWNER(hh::core_process::InfoVirtualSignalHandler);

hh::core_process::InfoVirtualSignalHandler::
InfoVirtualSignalHandler(const int &flag, const SetSignals &set)
    //: BaseSignalHandler(get_static_action(), flag, set)

{

}
#endif
