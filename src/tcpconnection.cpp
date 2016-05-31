#include <tcpconnection.h>

#include <iostream>

TcpConnection::TcpConnection(const IpAddress &address)
{
    m_socket = 0;
    m_remote_address = address;
}


TcpConnection::TcpConnection(TcpSocket *socket)
{
    m_socket = socket;
    m_remote_address = socket->remoteAddress();
}


void TcpConnection::setEventManager(EventManager *event_manager)
{
    m_event_manager = event_manager;
}


void TcpConnection::setListener(ITcpConnectionListener *listener)
{
    m_listener = listener;
}


void TcpConnection::open()
{
    m_connection_state = OPENING;

    // If connection is already esablished
    if(m_socket != 0) {
        m_connection_state = ACTIVE;

        m_event_manager->registerClient(this);

        m_listener->onOpened();
        return;
    }

    m_socket = new TcpSocket();
    m_socket->setBlocking(false);

    try {
        m_socket->connect(m_remote_address);

        m_event_manager->registerClient(this);
    }
    catch(TcpSocketException& e) {
        // Failed to connect
        throw e;
    }
}


void TcpConnection::close()
{
    m_connection_state = CLOSING;

    if(m_socket != 0) {
        m_socket->close();
        delete m_socket;
    }

    m_event_manager->unregisterClient(this);

    m_connection_state = CLOSED;
    m_listener->onClosed();
}


void TcpConnection::send(std::string data)
{
    if(m_send_buffer.size() > 0) {
        m_send_buffer += data;
        return;
    }

    try{
        int bytes_sent = m_socket->send(data);

        // If less bytes were sent than needed,place the rest in buffer
        if(bytes_sent < data.size())
            m_send_buffer += data.substr(bytes_sent);
    }
    catch(TcpSocketWouldBlock &e) {
        // Inpossible to send data right now, put it in buffer
        m_send_buffer += data;
    }
    catch(TcpSocketException &e) {
        // Error occurred
        close();
    }
}



void TcpConnection::onIn()
{
    try {
        std::string incoming_data = m_socket->receive();

        m_listener->onReceived(incoming_data);
    }
    catch(TcpSocketWouldBlock &e) {
        return;
    }
    catch(TcpSocketException &e) {
        // Error occurred
        close();
    }
}


void TcpConnection::onOut()
{
    switch (m_connection_state) {
    case OPENING:
        m_connection_state = ACTIVE;
        m_listener->onOpened();
        break;

    case ACTIVE:
        // Send data in buffer
        break;
    }

}


void TcpConnection::onError()
{
    close();
}


int TcpConnection::getSocket()
{
    return m_socket->getSocketDescriptor();
}


bool TcpConnection::isPollingOut()
{
    // If waiting for connection to esablish
    if(m_connection_state == OPENING)
        return true;

    // If there is data,that was not sent
    if(m_send_buffer.size() > 0)
        return true;
}
