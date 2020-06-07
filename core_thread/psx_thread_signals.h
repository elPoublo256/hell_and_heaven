#pragma once
#include <signal.h>
#include "psx_thread.h"
namespace hh {
namespace threads {
/*!
 * \brief send_signal
 * send signal to running thread
 * \param pthread - thread
 * \param signal - code signal
 * \throw PSX_Thread_Errno_Error when pthread_kill return error code
 * \throw PSX_Thread_Error when thread has not runned (pthread_t _c_thread == NULL)
 */
void send_signal(const PSX_Thread& pthread, int signal);

void set_signal_mask(const PSX_Thread& pthread,)


}
}
