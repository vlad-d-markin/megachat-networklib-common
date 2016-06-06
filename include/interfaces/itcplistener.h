#ifndef ITCPLISTENER_H
#define ITCPLISTENER_H

#include "itcplistenerlistener.h"


class ITcpListener {
public:
    virtual void listen(int port) = 0;
    virtual void close() = 0;
    virtual void setListener(ITcpListenerListener * listener) = 0;
};

#endif
