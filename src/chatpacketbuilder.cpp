#include <chatpacketbuilder.h>


void ChatPacketBuilder::appendByte(std::string &packet, __uint8_t a)
{
    __uint8_t buffer[5] = {0};
    buffer[0] = a;
    packet.append((const char *)buffer);
}


void ChatPacketBuilder::append2Bytes(std::string &packet, __uint16_t a)
{

}


void ChatPacketBuilder::append4Bytes(std::string &packet, __uint32_t)
{

}




std::string ChatPacketBuilder::buildLogin(std::string login, std::string password)
{

}
