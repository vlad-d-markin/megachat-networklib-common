#ifndef ITCPLISTENERLISTENER_H
#define ITCPLISTENERLISTENER_H

#include <tcpsocket.h>

class ITcpListenerListener {
    virtual void onAccepted(TcpSocket socket) = 0;
    virtual void onClosed() = 0;
};

#endif
