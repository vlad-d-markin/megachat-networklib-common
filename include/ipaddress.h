#ifndef IPADDRESS_H
#define IPADDRESS_H


#include <string>


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>


#include "exceptions/ipaddressexception.h"



class IpAddress {
protected:
    struct sockaddr_in m_sockaddr_inet;    ///< Sockaddr structure

public:
    IpAddress();


    /**
     * @brief Create IP address container form string with valid IPv4 address.
     * @param ipaddress String with valid IPv4 address.
     */
    IpAddress(std::string ipaddress, int port);



    /**
     * @brief Copy IP address container
     * @param address Other address
     */
    IpAddress(const IpAddress& address);



    ~IpAddress();



    const struct sockaddr_in * getSockAddr() const;


    int getPort() const;


    void setPort(int port);


    void setIpAddress(const std::string &ipaddress);


    void setIpAddress(const IpAddress &ipaddress);


    void setIpAddress(struct sockaddr_in addr, socklen_t addrlen);


    std::string toString() const;


    static IpAddress inAddrAny(int port);


protected:
    struct sockaddr_in ipStrToSockAddr(const std::string& ipaddress, int port);


};

#endif
