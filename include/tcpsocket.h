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
    
    bool m_is_blocking;
    bool m_is_listening;
    
    struct sockaddr_storage m_remote_addr;
    socklen_t m_remote_addr_len;
    
public:
    TcpSocket();
    virtual ~TcpSocket();
    
    
    
    /**
     * @brief Set socket mode
     * @param blocking Whether socket should be in blocking mode or not
     */
    void SetBlocking(bool blocking);
    
    
    
    /**
     * @brief Bind socket to a certain address
     * @param address Address to which bind socket
     */
    void Bind(const HostAddress& address);
    
    
    
    /**
     * @brief Swith socket to listening mode
     * @param backlog Backlog size
     */
    void Listen(unsigned int backlog);
    
    
    
    /**
     * @brief Connect to certain address
     * @param address Self explaining
     */
    void Connect(const HostAddress& address);
    
    
    
    /**
     * @brief If socket is in listening mode accept new connection
     * @return Connection with a client
     */
    TcpSocket * Accept();
    
    
    
    /**
     * @brief Set file descriptor manually
     * @param fd
     */
    void SetSocketFd(int fd);
    
    
    
    /**
     * @brief Send data to socket
     * @param data
     * @param len
     * @return Bytes sent
     */
    int Send(const char * data, int len);
    
    
    
    /**
     * @brief Receive data from socket
     * @param data
     * @param len
     * @return Bytes received
     */
    int Receive(char * data, int len);
    

    
    /**
     * @brief Close connection (stow listening)
     */
    void Close();    
    
private:
    void _SetBlocking();
    void _SetNonBlocking();
    void _SetRemoteAddress(struct sockaddr_storage remote_addr, socklen_t addr_len);
};



// =============================================================================
// Exeptions
class TcpSocketExeption : public Exeption {
public:
    TcpSocketExeption(std::string reason = getErrorDescription(errno));
    TcpSocketExeption(int error_code = errno);
    virtual ~TcpSocketExeption();
    
private:
    static std::string getErrorDescription(int error_code);
};

class TcpSocketWouldBlock : public TcpSocketExeption {
public:
    TcpSocketWouldBlock() : TcpSocketExeption("No reason") {}
};

#endif