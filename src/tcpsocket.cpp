#include "../include/tcpsocket.h"


#include <stdlib.h>
#include <string.h>
#include<iostream>

TcpSocket::TcpSocket() {
    m_is_blocking = true;
    m_is_listening = false;
    
    memset(&m_remote_addr, 0, sizeof(m_remote_addr));
    m_remote_addr_len = sizeof(m_remote_addr);
    
    m_socket_d = socket(AF_INET, SOCK_STREAM, 0);
    
    if(m_socket_d < 0) {
        // Trow exeption
         throw TcpSocketExeption(errno);
    }
}



TcpSocket::~TcpSocket() {
    Close();
}



void TcpSocket::SetSocketFd(int fd) {
    Close();
    m_socket_d = fd;
}



void TcpSocket::SetBlocking(bool blocking) {
    if(m_is_blocking == blocking)
        return;
    
    m_is_blocking = blocking;
    
    if(blocking) {
        _SetBlocking();
    }
    else {
        _SetNonBlocking();
    }
}



void TcpSocket::_SetBlocking() {
    int flags; 

    // Get old flags
    if ((flags = fcntl(m_socket_d, F_GETFL, 0)) < 0) { 
        // Handle error 
        throw TcpSocketExeption(errno);
    } 

    // Set blocking
    if (fcntl(m_socket_d, F_SETFL, flags & (~O_NONBLOCK)) < 0) 
    { 
        throw TcpSocketExeption(errno);
    } 
}


void TcpSocket::_SetNonBlocking() {
    int flags; 

    // Get old flags
    if ((flags = fcntl(m_socket_d, F_GETFL, 0)) < 0) { 
        // Handle error 
        throw TcpSocketExeption(errno);
    } 

    // Set non-blocking
    if (fcntl(m_socket_d, F_SETFL, flags | O_NONBLOCK) < 0) 
    { 
        throw TcpSocketExeption(errno);
    } 
}



void TcpSocket::Bind(const HostAddress& address) {
    int status = bind(m_socket_d, address.m_addrinfo->ai_addr, address.m_addrinfo->ai_addrlen);
    
    if(status < 0) {
        throw TcpSocketExeption(errno);
    }
}



void TcpSocket::Listen(unsigned int backlog) {
    int status = listen(m_socket_d, backlog);
    
    if(status < 0) {
        throw TcpSocketExeption(errno);
    }
    
    m_is_listening = true;
}



void TcpSocket::Connect(const HostAddress& address) {
    int status = connect(m_socket_d, address.m_addrinfo->ai_addr, address.m_addrinfo->ai_addrlen);
    
    if(status < 0) {
        throw TcpSocketExeption(errno);
    }
    
    
    // Is it bad?
    struct sockaddr_storage remote;
    memcpy(&remote, address.m_addrinfo->ai_addr, address.m_addrinfo->ai_addrlen);
    
    _SetRemoteAddress(remote, address.m_addrinfo->ai_addrlen);
    
    m_is_listening = false;
}



void TcpSocket::Close() {
    shutdown(m_socket_d, SHUT_RD);
    close(m_socket_d);
    
    m_is_listening = false;
}



int TcpSocket::Send(const char * data, int len){
    const char * data_to_send = data;
    unsigned int data_len = len;
    
    if(m_is_blocking)
        return send(m_socket_d, data_to_send, data_len, 0);
    
    int bytes_sent = send(m_socket_d, data_to_send, data_len, 0);
    
    if(bytes_sent < 0) {
        switch(errno) {
            case EWOULDBLOCK:
                // Throw something
                throw TcpSocketWouldBlock();
                break;
                
            default:
                throw TcpSocketExeption(errno);
        }
    }
    
    return bytes_sent;
}



int TcpSocket::Receive(char * data, int len) {
    char * receive_buffer = data;
    unsigned int max_data_len = len;
    
    if(m_is_blocking)
        return recv(m_socket_d, receive_buffer, max_data_len, 0);
    
    int bytes_received = recv(m_socket_d, receive_buffer, max_data_len, 0);
    
    if(bytes_received < 0) {
        switch(errno) {
            case EWOULDBLOCK:
                // Throw something
                throw TcpSocketWouldBlock();
                break;
                
            default:
                throw TcpSocketExeption(errno);
        }
    }
    
    return bytes_received;
}



TcpSocket *  TcpSocket::Accept() {
    if(!m_is_listening) {
        throw TcpSocketExeption("Socket is not in listening mode");
    }
    
    struct sockaddr_storage remote_addr;
    socklen_t addr_len;
 
    
    int new_socket_fd = accept(m_socket_d, (struct sockaddr *)&remote_addr, &addr_len);
    
    if(new_socket_fd < 0) {
        switch(errno) {
            case EWOULDBLOCK:
                throw TcpSocketWouldBlock();
                
            default:
                throw TcpSocketExeption(errno);
        }
    }
    
    TcpSocket * socket = new TcpSocket();
    socket->SetSocketFd(new_socket_fd);
    socket->_SetRemoteAddress(remote_addr, addr_len);

    return socket;  
}



void TcpSocket::_SetRemoteAddress(struct sockaddr_storage remote_addr, socklen_t addr_len) {
    m_remote_addr = remote_addr;
    m_remote_addr_len = addr_len;
    
//    HostAddress h("google.com", "80");
//    h.setAddrInfo(&m_remote_addr, m_remote_addr_len);
//    std::cout << "Remote addr: " << h.toString() << std::endl;
}




// =============================================================================
// TcpSocketExeption

TcpSocketExeption::TcpSocketExeption(std::string reason) : Exeption(reason) {}

TcpSocketExeption::TcpSocketExeption(int error_code) : Exeption(getErrorDescription(error_code)) {}

TcpSocketExeption::~TcpSocketExeption() {}

std::string TcpSocketExeption::getErrorDescription(int error_code) {
    return std::string("TcpSocketExeption:") + strerror(error_code);
}






