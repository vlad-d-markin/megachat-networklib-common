#ifndef ICHATCONNECTIONLISTENER_H
#define ICHATCONNECTIONLISTENER_H


class IChatConnectionListener {
public:
    virtual void onOpened() = 0;
    virtual void onClosed() = 0;
    virtual void onLogin(std::string username, std::string password) = 0;
    virtual void onLoginAck() = 0;
    virtual void onLogout() = 0;
    virtual void onLogoutAck() = 0;
    virtual void onMessageOut(int message_id, std::string sender, std::string recipient, std::string message) = 0;
    virtual void onMessageOutAck(int message_id, char code) = 0;
    virtual void onMessageIn(int message_id, std::string sender, std::string recipient, std::string message) = 0;
    virtual void onMessageInAck(int message_id, char code) = 0;
    virtual void onContactListRequest() = 0;
    virtual void onContactListResponse(std::vector<std::string> contacts) = 0;
    virtual void onPresence(std::string username, char status) = 0;
    virtual void onPresenceAck(std::string username) = 0;
    virtual void onKeepAlive() = 0;
    virtual void onKeepAliveAck() = 0;
};

#endif
