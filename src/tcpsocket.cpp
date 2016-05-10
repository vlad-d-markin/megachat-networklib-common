#include "../include/tcpsocket.h"

TcpSocket::TcpSocket() {
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


void TcpSocket::Bind(const HostAddress& address) {
    int status = bind(m_socket_d, address.m_addrinfo->ai_addr, address.m_addrinfo->ai_addrlen);
    
    if(status < 0) {
        throw TcpSocketExeption(errno);
    }
}


void TcpSocket::Listen(unsigned int backlog) {
    int status = listen(m_socket_d, backlog) >= 0;
    
    if(status < 0) {
        throw TcpSocketExeption(errno);
    }
}


void TcpSocket::Connect(const HostAddress& address) {
    int status = connect(m_socket_d, address.m_addrinfo->ai_addr, address.m_addrinfo->ai_addrlen) >= 0;
    
    if(status < 0) {
        throw TcpSocketExeption(errno);
    }
}



void TcpSocket::Close() {
    shutdown(m_socket_d, SHUT_RD);
    close(m_socket_d);
}


int TcpSocket::Send(const char * data, int len){
    return send(m_socket_d, data, len, 0);
}

int TcpSocket::Receive(char * data, int len) {
    return recv(m_socket_d, data, len, 0);
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






