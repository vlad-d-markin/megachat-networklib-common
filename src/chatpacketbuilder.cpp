#include <chatpacketbuilder.h>




ByteBuffer ChatPacketBuilder::buildLogin(std::string login, std::string password)
{
    ByteBuffer packet;

    // Packet Code
    packet.appendByte(LOGIN);
    // Packet length (1 + 2 + 2 + login + 2 + password )
    packet.append2Bytes(::htons(7 + login.length() + password.length()));
    // Login length
    packet.append2Bytes(::htons(login.length()));
    // Login
    packet.append(login);
    // Password length
    packet.append2Bytes(::htons(password.length()));
    // Password
    packet.append(password);

    return packet;
}



ByteBuffer ChatPacketBuilder::buildLoginAck(u_int8_t code)
{
    ByteBuffer packet;

    packet.appendByte(LOGIN_ACK);
    packet.append2Bytes(::htons(4));
    packet.appendByte(code);

    return packet;
}



ByteBuffer ChatPacketBuilder::buildLogout()
{
    ByteBuffer packet;

    packet.appendByte(LOGOUT);
    packet.append2Bytes(::htons(3));

    return packet;
}



ByteBuffer ChatPacketBuilder::buildLogoutAck()
{
    ByteBuffer packet;

    packet.appendByte(LOGOUT_ACK);
    packet.append2Bytes(::htons(3));

    return packet;
}



ByteBuffer ChatPacketBuilder::buildMessageOut(std::string recipient, u_int32_t message_id, std::string message)
{
    ByteBuffer packet;

    packet.appendByte(MESSAGE_OUT);
    // Packet length
    packet.append2Bytes(::htons(11 + recipient.length() + message.length()));
    // Recipient length
    packet.append2Bytes(::htons(recipient.length()));
    // Recipient
    packet.append(recipient);
    // ID
    packet.append4Bytes(::htonl(message_id));
    // Message length
    packet.append2Bytes(::htons(message.length()));
    // Message
    packet.append(message);

    return packet;
}



ByteBuffer ChatPacketBuilder::buildMessageOutAck(u_int32_t message_id, u_int8_t code)
{
    ByteBuffer packet;

    packet.appendByte(MESSAGE_OUT_ACK);
    packet.append2Bytes(::htons(8));
    packet.append4Bytes(::htonl(message_id));
    packet.appendByte(code);

    return packet;
}



ByteBuffer ChatPacketBuilder::buildMessageIn(std::string sender, u_int32_t message_id, std::string message)
{
    ByteBuffer packet;

    packet.appendByte(MESSAGE_IN);
    packet.append2Bytes(::htons(11 + sender.length() + message.length()));
    packet.append2Bytes(::htons(sender.length()));
    packet.append(sender);
    packet.append4Bytes(::htonl(message_id));
    packet.append2Bytes(::htons(message.length()));
    packet.append(message);

    return packet;
}



ByteBuffer ChatPacketBuilder::buildMessageInAck(u_int32_t message_id, u_int8_t code)
{
    ByteBuffer packet;

    packet.appendByte(MESSAGE_IN_ACK);
    packet.append2Bytes(::htons(8));
    packet.append4Bytes(::htonl(message_id));
    packet.appendByte(code);

    return packet;
}



ByteBuffer ChatPacketBuilder::buildContactListRequest()
{
    ByteBuffer packet;

    packet.appendByte(CONTACT_LIST_REQUEST);
    packet.append2Bytes(::htons(3));

    return packet;
}



ByteBuffer ChatPacketBuilder::buildContactListResponse(std::vector<User> contacts)
{
    ByteBuffer packet;

    packet.appendByte(CONTACT_LIST_RESPONSE);
    packet.append2Bytes('a');
    packet.append2Bytes(::htons(contacts.size()));

    for(auto it = contacts.begin(); it != contacts.end(); it++) {
        packet.append2Bytes(::htons(it->username.length()));
        packet.append(it->username);
        packet.appendByte(it->status);
    }

    packet.setAt(1, ::htons(packet.size()));

    return packet;
}



ByteBuffer ChatPacketBuilder::buildPresence(std::string username, u_int8_t status)
{
    ByteBuffer packet;

    packet.appendByte(PRESENCE);
    packet.append2Bytes(::htons(4 + username.length()));
    packet.append(username);
    packet.appendByte(status);

    return packet;
}



ByteBuffer ChatPacketBuilder::buildPresenceAck(std::string username)
{
    ByteBuffer packet;

    packet.appendByte(PRESENCE_ACK);
    packet.append2Bytes(::htons(3 + username.length()));
    packet.append(username);

    return packet;
}



ByteBuffer ChatPacketBuilder::buildKeepAlive()
{
    ByteBuffer packet;

    packet.appendByte(KEEP_ALIVE);
    packet.append2Bytes(::htons(3));

    return packet;
}


ByteBuffer ChatPacketBuilder::buildKeepAliveAck()
{
    ByteBuffer packet;

    packet.appendByte(KEEP_ALIVE_ACK);
    packet.append2Bytes(::htons(3));

    return packet;
}






// Chat packet parser



char ChatPacketParser::getByte()
{
    char byte;

    if(m_buffer.length() < 1)
        throw WrongPacketException();

    byte = m_buffer[0];
    m_buffer = m_buffer.substr(1);

    return byte;
}


short int ChatPacketParser::getShort()
{
    short int a;

    if(m_buffer.length() < 2)
        throw WrongPacketException();

    a = (unsigned char)m_buffer[0] * 256 + (unsigned char)m_buffer[1];
    m_buffer = m_buffer.substr(2);

    return a;
}


int ChatPacketParser::getInt()
{
    int a;

    if(m_buffer.length() < 4)
        throw WrongPacketException();

    a = (unsigned char) m_buffer[0]  << 24 + (unsigned char) m_buffer[1]  << 16 + (unsigned char) m_buffer[2]  << 8 +(unsigned char) m_buffer[3];

    return a;
}

std::string ChatPacketParser::getString()
{
    short int len = getShort();

    if(m_buffer.length() < len)
        throw WrongPacketException();

    std::string str = m_buffer.substr(0, len);
    m_buffer = m_buffer.substr(len);

    return str;
}

