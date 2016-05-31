#include <ipaddress.h>


IpAddress::IpAddress()
{
    memset(&m_sockaddr_inet, 0, sizeof(struct sockaddr_in));
}


/// Create new IP address container from string
IpAddress::IpAddress(std::string ipaddress, int port)
{
    memset(&m_sockaddr_inet, 0, sizeof(struct sockaddr_in));

    m_sockaddr_inet = ipStrToSockAddr(ipaddress, port);
}



/// Copy existing IP address container
IpAddress::IpAddress(const IpAddress &address)
{
    memset(&m_sockaddr_inet, 0, sizeof(struct sockaddr_in));

    m_sockaddr_inet.sin_family = AF_INET;
    m_sockaddr_inet.sin_addr.s_addr = address.m_sockaddr_inet.sin_addr.s_addr;
    m_sockaddr_inet.sin_port = address.m_sockaddr_inet.sin_port;
}



/// Destroy IP address container
IpAddress::~IpAddress() {}



/// Convert string with IPv4 address to sockaddr_it structure
struct sockaddr_in IpAddress::ipStrToSockAddr(const std::string &ipaddress, int port)
{
    struct sockaddr_in sockaddr_inet;

    memset(&sockaddr_inet, 0, sizeof(struct sockaddr_in));

    int result = ::inet_pton(AF_INET, ipaddress.c_str(), &sockaddr_inet);

    sockaddr_inet.sin_family = AF_INET;
    sockaddr_inet.sin_port = ::htons(port);

    if(result == 1) {
        return sockaddr_inet;
    }

    if(result == 0){
        throw InvalidAddressException("Invalid IP address (" + ipaddress+ ")");
    }

    if(result < 0) {
        throw IpAddressException("Invalid address family", errno);
    }
}



/// Get pointer to sockaddr struct
const struct sockaddr_in * IpAddress::getSockAddr() const
{
    return &m_sockaddr_inet;
}



/// Get port
int IpAddress::getPort() const
{
    return ::ntohs(m_sockaddr_inet.sin_port);
}



/// Set port
void IpAddress::setPort(int port)
{
    if(port < 0) {
        throw InvalidPortException("Invalid port: " + std::to_string(port));
    }

    m_sockaddr_inet.sin_port = ::htons(port);
}



/// Set IP address
void IpAddress::setIpAddress(const std::string &ipaddress)
{
    struct sockaddr_in new_sockaddr = ipStrToSockAddr(ipaddress, getPort());
    m_sockaddr_inet.sin_addr = new_sockaddr.sin_addr;
    m_sockaddr_inet.sin_family = AF_INET;
}



void IpAddress::setIpAddress(const IpAddress &ipaddress)
{
//    m_sockaddr_inet
}


void IpAddress::setIpAddress(sockaddr_in addr, socklen_t addrlen)
{
    memset(&m_sockaddr_inet, 0, sizeof(struct sockaddr_in));
    memcpy(&m_sockaddr_inet, &addr, addrlen);
}


std::string IpAddress::toString() const
{
    char * ip = inet_ntoa(m_sockaddr_inet.sin_addr);

    return std::string(ip) + ":" + std::to_string(getPort());
}


IpAddress IpAddress::inAddrAny()
{
//    return IpAddress("0.0.0.0");
}
