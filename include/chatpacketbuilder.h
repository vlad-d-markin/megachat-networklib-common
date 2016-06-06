#ifndef CHATPACKETBUILDER_H
#define CHATPACKETBUILDER_H

#include <string>

#include <bytebuffer.h>


class ChatPacketBuilder {
protected:
    static void appendByte(ByteBuffer& packet, __uint8_t a);
    static void append2Bytes(ByteBuffer& packet, __uint16_t a);
    static void append4Bytes(ByteBuffer& packet, __uint32_t a);


public:
    enum PacketCodes {
        LOGIN = 0,
        LOGIN_ACK = 0
    };

    static ByteBuffer buildLogin(std::string login, std::string password);

};

#endif
