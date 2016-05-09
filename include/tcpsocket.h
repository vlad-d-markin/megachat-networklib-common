#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include "../include/hostaddress.h"

class TcpSocket {
private:
    
public:
    TcpSocket(HostAddress ip);
    virtual ~TcpSocket();
};


#endif