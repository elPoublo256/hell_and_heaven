#include "../../core_ipc/psx_sockets/base_socket.h"
#include "../../core_ipc/psx_sockets/psx_ip_adress.h"
#include "../../core_process/base_process.h"
#include "../../core_process/processes_controller.h"
#include "../../core_ipc/psx_sockets/psx_stream_sockets.h"
#include <stdexcept>
#include <iostream>

hh::psx_ip::PSX_IP_Adress adr_serv("127.0.0.1",4488);

class ProcessA : public hh::process::Base_Process
{
public:
    virtual void action() override
    {
        hh::core_ipc::psx_socket::PSX_Stream_Socket_Server
                <AF_INET,IPPROTO_TCP> server(adr_serv, 5);
        auto con = server.get_connection();
        void* buf = malloc(128);
        for(int i = 0; i < 5; i++)
        {
            auto s = con.psx_recv(buf,128,0);
            std::cout << "get "<<s<<"b from client"<<std::endl;
        }



      }

};

class ProcessB : public hh::process::Base_Process
{
    virtual void action() override
    {

        hh::core_ipc::psx_socket::PSX_Stream_Socket_Client
                <AF_INET,IPPROTO_TCP> client(adr_serv);

        for(int i = 0; i < 5; i++)
        {
          // client.psx_write(&i, sizeof (int));
          client.psx_send(&i,sizeof (int),0);
          sleep(1);
        }

    }


};



int main()
{
    ProcessA a;
    ProcessB b;
    hh::process::Process_Controllers cont;
    cont.run_process(a);
    sleep(2);
    cont.run_process(b);
    cont.whait_process(a,WUNTRACED);
    cont.whait_process(b,WUNTRACED);






}



