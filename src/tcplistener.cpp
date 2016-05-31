#include <tcplistener.h>

#include <exceptions/tcpsocketexception.h>

TcpListener::TcpListener() { }



void TcpListener::listen(int port)
{
    IpAddress addr_to_listen = IpAddress::inAddrAny(port);

    m_socket.setBlocking(false);

    m_socket.bind(addr_to_listen);

    m_socket.listen();
}


void TcpListener::close()
{
    m_socket.close();

    m_listener->onClosed();
}


bool TcpListener::isPollingOut()
{
    return false;
}


int TcpListener::getSocket()
{
    return m_socket.getSocketDescriptor();
}


void TcpListener::onIn()
{
    // New connection incoming
    try {
        TcpSocket * incoming = m_socket.accept();

        m_listener->onAccepted(incoming);
    }
    catch(TcpSocketException& e) {
        // Error while accepting
    }

}



void TcpListener::onOut() { }



void TcpListener::onError()
{
    close();
}
