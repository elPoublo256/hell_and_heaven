

add_library(psx_base_socket
             base_socket.h
             base_socket.cpp
             psx_adress.h psx_adress.cpp
             psx_udp_socket.h
             psx_ip_adress.h
             psx_ip_adress.cpp
             psx_datagramm_sockets.h
             psx_datagramm_sockets.cpp
             psx_stream_sockets.cpp
             psx_stream_sockets.h
             psx_tcp_socket.h
             )


target_link_libraries(psx_base_socket
    hh_exception
    psx_base_file)


