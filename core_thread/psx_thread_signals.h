#pragma once
#include <signal.h>
#include "psx_thread.h"
#include "../core_process/psx_signals.h"
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
void send_signal(const Base_PSX_Thread& pthread, int signal);

/*!
 * \brief set_signal_mask
 * \param pthread
 * \param set_signals - set of signals
 * \throw PSX_Thread_Errno_Error when pthread_sigmask return error code
 * \throw PSX_Thread_Error when thread has not runned (pthread_t _c_thread == NULL)
 * \return last signal mask
 */
core_process::SetSignals
set_signal_mask(const Base_PSX_Thread& pthread, const core_process::SetSignals& set_signals);


}
}
