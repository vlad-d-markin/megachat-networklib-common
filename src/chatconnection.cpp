#include <chatconnection.h>



ChatConnection::ChatConnection(IByteConnection *connection, IChatConnectionListener *listener)
{
    m_connection = connection;
    m_listener = listener;
}



void ChatConnection::sendLogin(std::string username, std::string password)
{

}



void ChatConnection::sendLoginAck()
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
    // Parse
}


void ChatConnection::onClosed()
{
    m_listener->onClosed();
}

