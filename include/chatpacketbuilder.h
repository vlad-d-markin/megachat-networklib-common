#ifndef CHATPACKETBUILDER_H
#define CHATPACKETBUILDER_H

#include <string>
#include <vector>
#include <netinet/in.h>


#include "bytebuffer.h"
#include "structuser.h"




class ChatPacketBuilder {

public:    
    enum ChatPacketCodes {
        LOGIN = 0,
        LOGIN_ACK,
        LOGOUT,
        LOGOUT_ACK,
        MESSAGE_OUT,
        MESSAGE_OUT_ACK,
        MESSAGE_IN,
        MESSAGE_IN_ACK,
        CONTACT_LIST_REQUEST,
        CONTACT_LIST_RESPONSE,
        PRESENCE,
        PRESENCE_ACK,
        KEEP_ALIVE,
        KEEP_ALIVE_ACK
    };

    static ByteBuffer buildLogin(std::string login, std::string password);
    static ByteBuffer buildLoginAck(u_int8_t code);
    static ByteBuffer buildLogout();
    static ByteBuffer buildLogoutAck();
    static ByteBuffer buildMessageOut(std::string recipient, u_int32_t message_id, std::string message);
    static ByteBuffer buildMessageOutAck(u_int32_t message_id, u_int8_t code);
    static ByteBuffer buildMessageIn(std::string sender, u_int32_t message_id, std::string message);
    static ByteBuffer buildMessageInAck(u_int32_t message_id, u_int8_t code);
    static ByteBuffer buildContactListRequest();

    static ByteBuffer buildContactListResponse(std::vector<User> contacts);

    static ByteBuffer buildPresence(std::string username, u_int8_t status);
    static ByteBuffer buildPresenceAck(std::string username);
    static ByteBuffer buildKeepAlive();
    static ByteBuffer buildKeepAliveAck();
};


class WrongPacketException {};


class ChatPacketParser {
private:
    std::string m_buffer;

public:
    ChatPacketParser(const std::string &buffer) : m_buffer(buffer) {}

    char getByte();
    short int getShort();
    int getInt();
    std::string getString();
};

#endif
