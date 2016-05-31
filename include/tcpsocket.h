#ifndef TCPSOCKET_H
#define TCPSOCKET_H


#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <string>


#include <exceptions/tcpsocketexception.h>
#include <ipaddress.h>



class TcpSocket {
private:
    int m_socket_fd;
    
    IpAddress m_remote_address;
    
public:
    TcpSocket();
    virtual ~TcpSocket();
    


    void setSocketDescriptor(int socket_fd);



    int getSocketDescriptor();


    void connect(const IpAddress& ipaddress);


    void bind(const IpAddress& ipaddress);
    
//private:
//    void _SetBlocking();
//    void _SetNonBlocking();
//    void _SetRemoteAddress(struct sockaddr_storage remote_addr, socklen_t addr_len);
};


#endif
