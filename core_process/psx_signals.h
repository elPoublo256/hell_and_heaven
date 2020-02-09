#pragma once
#include "signal.h"
#include "stdint.h"
#include <string>
#include <initializer_list>
namespace hh {


namespace core_process {


///send signal to process using kill()
void send_signal(const int&signal_code, const pid_t& pid);

///send signal to group using killpg()
void send_signal_to_group(const int&signal_code, pid_t& pidgrup);

void send_signal_to_self(const int& signal);

class SetSignals
{
  public:
    SetSignals();
    SetSignals(const int& signal);
    SetSignals(const std::initializer_list<int>& inilist);
    SetSignals(const sigset_t& c_sigset_prt);
    SetSignals(const SetSignals& copy);
    SetSignals(SetSignals&& rv_copy);
   /* ///like sigandset No in POSIX ore SUSv3/4 but in glibc
    SetSignals operator && ( const SetSignals& b);
    ///like sigorset
    SetSignals operator | ( const SetSignals& b);
    bool is_empty();
*/
    ///add signal using sigadd
    void add_signal(const int& signal_code);


    void delete_signal(const int& signalecode);

    const sigset_t* get_c_sigset() const;

    bool is_member(const int& signal) const noexcept;

  private:
    void set_empty();

    sigset_t __glibc_sigset_prt;

};

///create set with all signals like sigfillset()
SetSignals full_SetSignals();


/*!
 * \brief set_signal_mask - sigprogmasck-like function
 * the bater whay use other functions:
 * set_signal_mask(const SetSignals& set) for set signal mask
 * add_block_mask(const SetSignals& set) for add signals to curent masck
 * set_unblock_mask(const SetSignals& set) for remove signals from curent mask
 * SetSignals&& qurent_mask(); - get curent mask
 * \param how flag seting
 *  SIG_BLOCK - add curent masck
 *  SIG_UNBLOCK
 *  SIG_SETMASK
 * \param set
 * \return return qurent mask
 */
SetSignals set_signal_mask(const int& how, const SetSignals& set);

inline SetSignals set_signal_mask(const SetSignals& set)
{
    return set_signal_mask(SIG_SETMASK, set);
}

inline SetSignals add_block_mask(const SetSignals& set)
{
    return set_signal_mask(SIG_BLOCK,set);
}

inline SetSignals set_unblock_mask(const SetSignals& set)
{
    return set_signal_mask(SIG_UNBLOCK,set);
}


/*!
 * \brief qurent_mask
 * \return SetSignals with qurent masck of process
 */
SetSignals&& get_qurent_mask();

SetSignals&& get_whaiting_signals();






}

}

