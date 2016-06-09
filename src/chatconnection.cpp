#include <chatconnection.h>

#include <chatpacketbuilder.h>


ChatConnection::ChatConnection(IByteConnection *connection)
{
    m_connection = connection;
}


void ChatConnection::setListener(IChatConnectionListener *listener)
{
    m_listener = listener;
}


void ChatConnection::sendLogin(std::string username, std::string password)
{
    m_connection->send(ChatPacketBuilder::buildLogin(username, password).toString());
}


void ChatConnection::open()
{
    m_connection->open();
}


void ChatConnection::close()
{
    m_connection->close();
}


void ChatConnection::sendLoginAck(unsigned char code)
{

}



void ChatConnection::sendLogout()
{

}



void ChatConnection::sendLogoutAck()
{

}



void ChatConnection::sendMessageOut(int message_id, std::string recipient, std::string message)
{

}



void ChatConnection::sendMessageOutAck(int message_id, char code)
{

}



void ChatConnection::sendMessageIn(int message_id, std::string sender, std::string message)
{

}



void ChatConnection::sendMessageInAck(int message_id, char code)
{

}



void ChatConnection::sendContactListRequest()
{

}



void ChatConnection::sendContactListResponse(std::vector<User> contacts)
{

}



void ChatConnection::sendPresence(std::string username, char status)
{

}



void ChatConnection::sendPresenceAck(std::string username)
{

}



void ChatConnection::sendKeepAlive()
{

}



void ChatConnection::sendKeepAliveAck()
{

}



void ChatConnection::onOpened()
{
    m_listener->onOpened();
}



void ChatConnection::onReceived(std::string data)
{
    m_buffer += data;

    while(1) {
        if(m_buffer.length() < 3)
            return;

        int packet_length = (unsigned char)m_buffer[1] * 256 + (unsigned char)m_buffer[2];
        if(m_buffer.length() < packet_length)
            return;

        parsePacket();

        m_buffer = m_buffer.substr(packet_length);
    }
}




void ChatConnection::onClosed()
{
    m_listener->onClosed();
}



void ChatConnection::parsePacket()
{
    ChatPacketParser parser(m_buffer);

    char packet_code = parser.getByte();
    parser.getShort();

    switch (packet_code) {
    case ChatPacketBuilder::LOGIN:
    {
        std::string username = parser.getString();
        std::string password = parser.getString();

        m_listener->onLogin(username, password);
    }
        break;

    default:
        close();
        break;
    }
}
