#ifndef CHATCONNECTION_H
#define CHATCONNECTION_H



#include "interfaces/ichatconnection.h"
#include "interfaces/ichatconnectionlistener.h"
#include "interfaces/ibyteconnectionlistener.h"
#include "interfaces/ibyteconnection.h"



class ChatConnection : public IChatConnection, public IByteConnectionListener {
protected:
    IByteConnection * m_connection;
    IChatConnectionListener * m_listener;

public:
    ChatConnection(IByteConnection * connection, IChatConnectionListener * listener);


    virtual void sendLogin(std::string username, std::string password);
    virtual void sendLoginAck();
    virtual void sendLogout();
    virtual void sendLogoutAck();
    virtual void sendMessageOut(int message_id, std::string recipient, std::string message);
    virtual void sendMessageOutAck(int message_id, char code) = 0;
    virtual void sendMessageIn(int message_id, std::string sender, std::string message);
    virtual void sendMessageInAck(int message_id, char code);
    virtual void sendContactListRequest();
    virtual void sendContactListResponse(std::vector<User> contacts);
    virtual void sendPresence(std::string username, char status);
    virtual void sendPresenceAck(std::string username);
    virtual void sendKeepAlive();
    virtual void sendKeepAliveAck();


    virtual void onOpened();
    virtual void onReceived(std::string data);
    virtual void onClosed();
};

#endif
