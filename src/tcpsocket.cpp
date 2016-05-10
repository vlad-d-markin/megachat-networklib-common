#include "../include/tcpsocket.h"

TcpSocket::TcpSocket() {
    m_is_blocking = true;
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
}


void TcpSocket::Connect(const HostAddress& address) {
    int status = connect(m_socket_d, address.m_addrinfo->ai_addr, address.m_addrinfo->ai_addrlen);
    
    if(status < 0) {
        throw TcpSocketExeption(errno);
    }
}



void TcpSocket::Close() {
    shutdown(m_socket_d, SHUT_RD);
    close(m_socket_d);
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
    
}

















// =============================================================================
// TcpSocketExeption

TcpSocketExeption::TcpSocketExeption(std::string reason) : Exeption(reason) {}

TcpSocketExeption::TcpSocketExeption(int error_code) : Exeption(getErrorDescription(error_code)) {}

TcpSocketExeption::~TcpSocketExeption() {}

std::string TcpSocketExeption::getErrorDescription(int error_code) {
    return strerror(error_code);
}






