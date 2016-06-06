#ifndef TCPLISTENER_H
#define TCPLISTENER_H


#include "interfaces/itcplistener.h"
#include "interfaces/ipollingclient.h"
#include "interfaces/itcplistenerlistener.h"
#include "tcpsocket.h"



class TcpListener : public ITcpListener, public IPollingClient {
protected:
    TcpSocket m_socket;

    ITcpListenerListener * m_listener;

public:
    TcpListener();


    virtual void listen(int port);


    virtual void setListener(ITcpListenerListener * listener);


    virtual void close();


    virtual int getSocket();


    virtual bool isPollingOut();


    virtual void onIn();


    virtual void onOut();


    virtual void onError();
};

#endif
