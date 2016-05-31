#ifndef ITCPCONNECTION_H
#define ITCPCONNECTION_H

#include <interfaces/ibyteconnection.h>
#include <interfaces/itcpconnectionlistener.h>
#include <eventmanager.h>

class ITcpConnection : public IByteConnection {
public:
    virtual void setEventManager(EventManager * event_manager) = 0;
    virtual void setListener(ITcpConnectionListener * listener) = 0;
};

#endif
