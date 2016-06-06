#include <chatpacketbuilder.h>


void ChatPacketBuilder::appendByte(ByteBuffer &packet, __uint8_t a)
{
    packet.appendRaw((char *)&a, 1);
}


void ChatPacketBuilder::append2Bytes(ByteBuffer &packet, __uint16_t a)
{
    packet.appendRaw((char *)&a, 2);
//    const char * d = (char *)&a;
//    appendByte(packet, d[0]);
//    appendByte(packet, d[1]);
}


void ChatPacketBuilder::append4Bytes(ByteBuffer &packet, __uint32_t a)
{
    packet.appendRaw((char *)&a, 4);
}




ByteBuffer ChatPacketBuilder::buildLogin(std::string login, std::string password)
{
    ByteBuffer login_pack;
    appendByte(login_pack, LOGIN);

    const short packet_length = 1 + 2 + 2 + login.length() + 2 + password.length();
    append2Bytes(login_pack, packet_length);
    append2Bytes(login_pack, login.length());
//    login_pack.appendRaw(login.c_str(), login.length());
    append2Bytes(login_pack, password.length());
//    login_pack.appendString(password);

    return login_pack;
}
