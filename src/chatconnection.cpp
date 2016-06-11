#include <chatconnection.h>

#include <chatpacketbuilder.h>

#include <iostream>


ChatConnection::ChatConnection(IByteConnection *connection)
{
    m_connection = connection;
}


void ChatConnection::setListener(IChatConnectionListener *listener)
{
    m_listener = listener;
}


void ChatConnection::open()
{
    m_connection->open();
}


void ChatConnection::close()
{
    m_connection->close();
}


void ChatConnection::sendLogin(std::string username, std::string password)
{
    m_connection->send(ChatPacketBuilder::buildLogin(username, password).toString());
}


void ChatConnection::sendLoginAck(unsigned char code)
{
    m_connection->send(ChatPacketBuilder::buildLoginAck(code).toString());
}



void ChatConnection::sendLogout()
{
    m_connection->send(ChatPacketBuilder::buildLogout().toString());
}



void ChatConnection::sendLogoutAck()
{
    m_connection->send(ChatPacketBuilder::buildLogoutAck().toString());
}



void ChatConnection::sendMessageOut(int message_id, std::string recipient, std::string message)
{
    m_connection->send(ChatPacketBuilder::buildMessageOut(recipient, message_id, message).toString());
}



void ChatConnection::sendMessageOutAck(int message_id, char code)
{
    m_connection->send(ChatPacketBuilder::buildMessageOutAck(message_id, code).toString());
}



void ChatConnection::sendMessageIn(int message_id, std::string sender, std::string message)
{
    m_connection->send(ChatPacketBuilder::buildMessageOut(sender, message_id, message).toString());
}



void ChatConnection::sendMessageInAck(int message_id, char code)
{
    m_connection->send(ChatPacketBuilder::buildMessageInAck(message_id, code).toString());
}



void ChatConnection::sendContactListRequest()
{
    m_connection->send(ChatPacketBuilder::buildContactListRequest().toString());
}



void ChatConnection::sendContactListResponse(std::vector<User> contacts)
{
    m_connection->send(ChatPacketBuilder::buildContactListResponse(contacts).toString());
}



void ChatConnection::sendPresence(std::string username, char status)
{
    m_connection->send(ChatPacketBuilder::buildPresence(username, status).toString());
}



void ChatConnection::sendPresenceAck(std::string username)
{
    m_connection->send(ChatPacketBuilder::buildPresenceAck(username).toString());
}



void ChatConnection::sendKeepAlive()
{
    m_connection->send(ChatPacketBuilder::buildKeepAlive().toString());
}



void ChatConnection::sendKeepAliveAck()
{
    m_connection->send(ChatPacketBuilder::buildKeepAliveAck().toString());
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

    // Parse packet code
    char packet_code = parser.getByte();
    // Skip packet length
    parser.getShort();

    switch (packet_code) {
        case ChatPacketBuilder::LOGIN:
        {
            std::string username = parser.getString();
            std::string password = parser.getString();

            m_listener->onLogin(username, password);
        }
            break;


        case ChatPacketBuilder::LOGIN_ACK:
        {
            char login_ack_code = parser.getByte();

            m_listener->onLoginAck(login_ack_code);
        }
            break;


        case ChatPacketBuilder::LOGOUT:
            m_listener->onLogout();
            break;


        case ChatPacketBuilder::LOGOUT_ACK:
            m_listener->onLogoutAck();
            break;


        case ChatPacketBuilder::MESSAGE_OUT:
        {
            std::string recipient = parser.getString();
            int message_id = parser.getInt();
            std::string message = parser.getString();

            m_listener->onMessageOut(recipient, message_id, message);
        }
            break;


        case ChatPacketBuilder::MESSAGE_OUT_ACK:
        {
            int message_id = parser.getInt();
            char code = parser.getByte();

            m_listener->onMessageOutAck(message_id, code);
        }
            break;


        case ChatPacketBuilder::MESSAGE_IN:
        {
            std::string sender = parser.getString();
            int message_id = parser.getInt();
            std::string message = parser.getString();

            m_listener->onMessageIn(sender, message_id, message);
        }
            break;


        case ChatPacketBuilder::MESSAGE_IN_ACK:
        {
            int message_id = parser.getInt();
            char code = parser.getByte();

            m_listener->onMessageInAck(message_id, code);
        }
            break;


        case ChatPacketBuilder::CONTACT_LIST_REQUEST:
            m_listener->onContactListRequest();
            break;


        case ChatPacketBuilder::CONTACT_LIST_RESPONSE:
        {
            // Parse contacts
        }
            break;

        case ChatPacketBuilder::PRESENCE:
        {
            std::string username = parser.getString();
            char status = parser.getByte();

            m_listener->onPresence(username, status);
        }
            break;


        case ChatPacketBuilder::PRESENCE_ACK:
        {
            std::string username = parser.getString();

            m_listener->onPresenceAck(username);
        }
            break;


        case ChatPacketBuilder::KEEP_ALIVE:
            m_listener->onKeepAlive();
            break;


        case ChatPacketBuilder::KEEP_ALIVE_ACK:
            m_listener->onKeepAliveAck();
            break;

        default:
            close();
            break;
        }
}
