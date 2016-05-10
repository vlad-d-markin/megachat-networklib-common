#include "../include/hostaddress.h"
#include "../include/exeption.h"

#include <string.h>
#include <exception>
#include <stddef.h>
#include <arpa/inet.h>


HostAddress::HostAddress(const std::string& address, const std::string& port) {
    getAddrInfo(address, port);
}



HostAddress::~HostAddress() {
    freeaddrinfo(m_addrinfo);
}



void HostAddress::setAddress(const std::string& address, const std::string& port) {
    freeaddrinfo(m_addrinfo);
    
    getAddrInfo(address, port);
}



std::string HostAddress::toString() const {
    std::string addr;
    
    struct sockaddr_in *ipv4 = (struct sockaddr_in *)m_addrinfo->ai_addr;
    char ipAddress[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(ipv4->sin_addr), ipAddress, INET_ADDRSTRLEN);
    
    addr = ipAddress;
    
    return addr;    
}



void HostAddress::getAddrInfo(const std::string& address, const std::string& port) {
    const char * node = address.data();
    
    const char * service = NULL;
    if(port.length() > 0) {
        service = port.data();
    }
    
    int status;
    struct addrinfo hints;
    
    memset(&hints, 0, sizeof(hints));
    
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    
    if((status = getaddrinfo(node, service, &hints, &m_addrinfo)) != 0) {
        throw Exeption(gai_strerror(status));
    }
}