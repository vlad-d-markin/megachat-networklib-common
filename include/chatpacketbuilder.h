#ifndef CHATPACKETBUILDER_H
#define CHATPACKETBUILDER_H

#include <string>

class ChatPacketBuilder {
protected:
    static void appendByte(std::string& packet, __uint8_t a);
    static void append2Bytes(std::string& packet, __uint16_t a);
    static void append4Bytes(std::string &packet, __uint32_t);


public:
    static std::string buildLogin(std::string login, std::string password);

};

#endif
