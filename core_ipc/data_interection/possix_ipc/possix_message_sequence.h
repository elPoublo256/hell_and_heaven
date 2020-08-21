#pragma once
#include "../psx_base_message_sequenc.h"
#include "../../../core_files/psx_files.h"
#include <sys/stat.h>
#include <mqueue.h>
namespace hh {
namespace core_ipc {
namespace possix_ipc {


class BasePOSSIX_MESS_Peer
{
public:
    BasePOSSIX_MESS_Peer(const mqd_t& mqd);
    BasePOSSIX_MESS_Peer(const char* name, int openflg);
    BasePOSSIX_MESS_Peer(const std::string& name, int openflg);

    ///for reate new sequence with openflag O_CREAT with default atribut (atr = NULL)
    BasePOSSIX_MESS_Peer(const char* name,const int& flag,
                         const mode_t& mode);

    BasePOSSIX_MESS_Peer(const char* name,const int& flag,
                         const mode_t& mode,
                         const struct mq_attr& atr);
protected:
    mqd_t __mq_id;


};

}
}
}
