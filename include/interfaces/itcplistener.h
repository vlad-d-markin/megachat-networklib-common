#ifndef ITCPLISTENER_H
#define ITCPLISTENER_H

class ITcpListener {
public:
    virtual void listen(int port) = 0;
};

#endif
