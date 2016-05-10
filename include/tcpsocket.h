#ifndef TCPSOCKET_H
#define TCPSOCKET_H

class TcpSocket;

#include "../include/hostaddress.h"
#include "../include/exeption.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include <string>

//class TcpSocketExeption;

class TcpSocket {
private:
    int m_socket_d;
    
public:
    TcpSocket();
    virtual ~TcpSocket();
    
    void Bind(const HostAddress& address);
    void Listen(unsigned int backlog);
    void Connect(const HostAddress& address);
    TcpSocket * Accept();
    void SetSocketFd(int fd);
    
    int Send(const char * data, int len);
    int Receive(char * data, int len);
    
    void Close();    
};



class TcpSocketExeption : public Exeption {
public:
    TcpSocketExeption(std::string reason = getErrorDescription(errno));
    TcpSocketExeption(int error_code = errno);
    virtual ~TcpSocketExeption();
    
private:
    static std::string getErrorDescription(int error_code);
};

#endif