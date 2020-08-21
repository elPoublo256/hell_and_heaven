#include "possix_message_sequence.h"
hh::core_ipc::possix_ipc::BasePOSSIX_MESS_Peer::BasePOSSIX_MESS_Peer(const char *name, int openflg)
{
    __mq_id = mq_open(name,openflg);
}

hh::core_ipc::possix_ipc::BasePOSSIX_MESS_Peer::BasePOSSIX_MESS_Peer(const std::__cxx11::string &name, int openflg)
{
  __mq_id = mq_open(name.c_str(),openflg);
}

hh::core_ipc::possix_ipc::BasePOSSIX_MESS_Peer::BasePOSSIX_MESS_Peer(const char *name,
                                                                     const int &flag,
                                                                     const mode_t &mode,
                                                                     const mq_attr &atr)
{
    auto __atr = atr;
    __mq_id = mq_open(name,flag, mode, &__atr);
}

hh::core_ipc::possix_ipc::BasePOSSIX_MESS_Peer::BasePOSSIX_MESS_Peer(const char *name, const int &flag, const mode_t &mode)
{
    __mq_id = mq_open(name,flag, mode, NULL);
}


