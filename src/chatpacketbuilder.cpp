#include <chatpacketbuilder.h>




ByteBuffer ChatPacketBuilder::buildLogin(std::string login, std::string password)
{
    ByteBuffer packet;

    // Packet Code
    packet.appendByte(LOGIN);
    // Packet length (1 + 2 + 2 + login + 2 + password )
    packet.append2Bytes(7 + login.length() + password.length());
    // Login length
    packet.append2Bytes(login.length());
    // Login
    packet.append(login);
    // Password length
    packet.append2Bytes(password.length());
    // Password
    packet.append(password);

    return packet;
}



ByteBuffer ChatPacketBuilder::buildLoginAck(u_int8_t code)
{
    ByteBuffer packet;

    packet.appendByte(LOGIN_ACK);
    packet.append2Bytes(4);
    packet.appendByte(code);

    return packet;
}



ByteBuffer ChatPacketBuilder::buildLogout()
{
    ByteBuffer packet;

    packet.appendByte(LOGOUT);
    packet.append2Bytes(3);

    return packet;
}



ByteBuffer ChatPacketBuilder::buildLogoutAck()
{
    ByteBuffer packet;

    packet.appendByte(LOGOUT_ACK);
    packet.append2Bytes(3);

    return packet;
}



ByteBuffer ChatPacketBuilder::buildMessageOut(std::string recipient, u_int32_t message_id, std::string message)
{
    ByteBuffer packet;

    packet.appendByte(MESSAGE_OUT);
    // Packet length
    packet.append2Bytes(11 + recipient.length() + message.length());
    // Recipient length
    packet.append2Bytes(recipient.length());
    // Recipient
    packet.append(recipient);
    // ID
    packet.append4Bytes(message_id);
    // Message length
    packet.append2Bytes(message.length());
    // Message
    packet.append(message);

    return packet;
}



ByteBuffer ChatPacketBuilder::buildMessageOutAck(u_int32_t message_id, u_int8_t code)
{
    ByteBuffer packet;

    packet.appendByte(MESSAGE_OUT_ACK);
    packet.append2Bytes(8);
    packet.append4Bytes(message_id);
    packet.appendByte(code);

    return packet;
}

