#ifndef HOSTADDRESS_H
#define HOSTADDRESS_H

#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

class HostAddress;

#include "../include/tcpsocket.h"

class HostAddress {
private:
    friend TcpSocket;
    struct addrinfo * m_addrinfo;
    
public:
    /**
     * @brief Create new object containing struct sockaddr from given hostname or IP
     * Actually struct addrinfo
     * @param address hostname or IP
     */
    HostAddress(const std::string& address, const std::string& port = "");
    
    
    virtual ~HostAddress();
    
    
    
    /**
     * @brief Set new IP or hostname. Old addrinfo is removed.
     * @param address new IP address or hostname
     */
    void setAddress(const std::string& address, const std::string& port = "");
    
    
    
    /**
     * @brief Get text representation of current IP address that is represented 
     *        by thsi object 
     * @return string like 8.8.8.8
     */
    std::string toString() const;
    
private:
    void getAddrInfo(const std::string& address, const std::string& port);
    
};

#endif /* HOSTADDRESS_H */

