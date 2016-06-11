#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <string>

#include "interfaces/itcpconnection.h"
#include "tcpsocket.h"
#include "interfaces/itcpconnectionlistener.h"
#include "interfaces/ipollingclient.h"
#include "ipaddress.h"
#include "eventmanager.h"



class TcpConnection : public ITcpConnection, public IPollingClient {
public:
    TcpConnection(const IpAddress& address);

    TcpConnection(TcpSocket * socket);

    virtual void setEventManager(EventManager * event_manager);

    virtual void setListener(ITcpConnectionListener * listener);

    virtual void open();

    virtual void close();

    virtual void send(std::string data);



    virtual void onIn();

    virtual void onOut();

    virtual void onError();

    virtual int  getSocket();

    virtual bool isPollingOut();

protected:
    enum State {
        CLOSED,
        CLOSING,
        OPENING,
        ACTIVE
    };

    IpAddress                   m_remote_address;
    TcpSocket *                 m_socket;
    ITcpConnectionListener *    m_listener;
    State                       m_connection_state;
    std::string                 m_send_buffer;
    EventManager *              m_event_manager;

};

#endif
