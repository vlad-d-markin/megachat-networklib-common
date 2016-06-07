#ifndef CHATPACKETBUILDER_H
#define CHATPACKETBUILDER_H

#include <string>


#include "bytebuffer.h"




class ChatPacketBuilder {

public:    
    enum ChatPacketCodes {
        LOGIN = 0,
        LOGIN_ACK,
        LOGOUT,
        LOGOUT_ACK,
        MESSAGE_OUT,
        MESSAGE_OUT_ACK
    };

    static ByteBuffer buildLogin(std::string login, std::string password);
    static ByteBuffer buildLoginAck(u_int8_t code);
    static ByteBuffer buildLogout();
    static ByteBuffer buildLogoutAck();
    static ByteBuffer buildMessageOut(std::string recipient, u_int32_t message_id, std::string message);
    static ByteBuffer buildMessageOutAck(u_int32_t message_id, u_int8_t code);

};

#endif
