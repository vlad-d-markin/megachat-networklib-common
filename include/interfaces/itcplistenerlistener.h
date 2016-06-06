#ifndef ITCPLISTENERLISTENER_H
#define ITCPLISTENERLISTENER_H

#include "../tcpsocket.h"


class ITcpListenerListener {
public:
    virtual void onAccepted(TcpSocket * socket) = 0;
    virtual void onClosed() = 0;
};

#endif
