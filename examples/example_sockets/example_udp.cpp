#include "../../core_ipc/psx_sockets/base_socket.h"
#include "../../core_ipc/psx_sockets/psx_ip_adress.h"
#include "../../core_process/base_process.h"
#include "../../core_process/processes_controller.h"
#include <stdexcept>
#include <iostream>
class ProcessA : public hh::process::Base_Process
{
public:
    virtual void action() override
    {

        hh::core_ipc::psx_socket::PSX_DataGramSocketBase
                <AF_INET, IPPROTO_UDP> sock;

        hh::psx_ip::PSX_IP_Adress adr_a("127.0.0.2",4488);
        hh::psx_ip::PSX_IP_Adress adr_b("127.0.0.3",4488);
        hh::psx_ip::PSX_IP_Adress adr_b_cop(adr_b);

        sock.psx_bind(adr_a);
        sleep(1);
        std::string mess("qwerty");
        for(;;){
            sleep(1);
          auto res_send = sock.psx_send_to(mess.data(),mess.size(),adr_b_cop,0);
          std::cout << "send to b "<<res_send<<'b'<<std::endl;

        }

    }



};

class ProcessB : public hh::process::Base_Process
{
    virtual void action() override
    {

        hh::core_ipc::psx_socket::PSX_DataGramSocketBase
                <AF_INET, IPPROTO_UDP> sock;

        hh::psx_ip::PSX_IP_Adress adr_a("127.0.0.2",4488);
        hh::psx_ip::PSX_IP_Adress adr_b("127.0.0.3",4488);

        sock.psx_bind(adr_b);
        void* buf = malloc(1028);
        for(;;){
            //auto s  = sock.psx_read(buf,1028);
            auto s = sock.psx_recv_from(buf,1028,adr_a,MSG_WAITALL);
            std::cout << "read from bufer "<<s<<'b'<<std::endl;

        }


    }


};



int main()
{
    ProcessA a;
    ProcessB b;
    hh::process::Process_Controllers cont;
    cont.run_process(a);
    sleep(1);
    cont.run_process(b);
    cont.whait_process(a,WUNTRACED);

    cont.whait_process(b,WUNTRACED);






}



