#ifndef ICHATCONNECTION_H
#define ICHATCONNECTION_H

#include <string>
#include <vector>


#include "../structuser.h"



class IChatConnection {
public:
    virtual void open() = 0;
    virtual void close() = 0;

    virtual void sendLogin(std::string username, std::string password) = 0;
    virtual void sendLoginAck(unsigned char code) = 0;
    virtual void sendLogout() = 0;
    virtual void sendLogoutAck() = 0;
    virtual void sendMessageOut(int message_id, std::string recipient, std::string message) = 0;
    virtual void sendMessageOutAck(int message_id, char code) = 0;
    virtual void sendMessageIn(int message_id, std::string sender, std::string message) = 0;
    virtual void sendMessageInAck(int message_id, char code) = 0;
    virtual void sendContactListRequest() = 0;
    virtual void sendContactListResponse(std::vector<User> contacts) = 0;
    virtual void sendPresence(std::string username, char status) = 0;
    virtual void sendPresenceAck(std::string username) = 0;
    virtual void sendKeepAlive() = 0;
    virtual void sendKeepAliveAck() = 0;
};

#endif
