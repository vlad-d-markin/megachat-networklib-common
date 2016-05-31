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


#define TCP_SOCKET_LISTEN_BACKLOG 100
#define TCP_SOCKET_RECEIVE_BUFFER_SIZE 1024


class TcpSocket {
private:
    int m_socket_fd;
    
    IpAddress m_remote_address;

    bool m_listening;

    bool m_blocking;
    
public:
    TcpSocket();


    TcpSocket(int socket_fd, const IpAddress &remote_addr);


    virtual ~TcpSocket();
    

    void setBlocking(bool is_blocking);


    void setSocketDescriptor(int socket_fd);


    int getSocketDescriptor();


    bool isListening();


    void connect(const IpAddress& ipaddress);


    void bind(const IpAddress& ipaddress);


    void listen();


    TcpSocket * accept();


    void close();


    int send(std::string data);


    std::string receive(int maxlen = -1);


    
private:
    void setNonBlockingMode();

    void setBlockingMode();


};


#endif
