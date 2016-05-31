#include <tcpsocket.h>


TcpSocket::TcpSocket()
{
    m_socket_fd = ::socket(AF_INET, SOCK_STREAM, 0);

    m_listening = false;

    m_blocking = true;
}


TcpSocket::TcpSocket(int socket_fd, const IpAddress &remote_addr)
{
    m_socket_fd = socket_fd;
    m_remote_address = remote_addr;

    m_listening = false;

    m_blocking = true;
}


TcpSocket::~TcpSocket()
{
    ::close(m_socket_fd);
}


void TcpSocket::setBlocking(bool is_blocking)
{
    if(m_blocking == is_blocking)
        return;

    m_blocking = is_blocking;

    if(m_blocking)
        setBlockingMode();
    else
        setNonBlockingMode();
}


void TcpSocket::setSocketDescriptor(int fd)
{
    ::close(m_socket_fd);
    m_socket_fd = fd;
}



int TcpSocket::getSocketDescriptor()
{
    return m_socket_fd;
}



bool TcpSocket::isListening()
{
    return m_listening;
}



void TcpSocket::connect(const IpAddress &ipaddress)
{
    const struct sockaddr * remote_addr = (const struct sockaddr *) (ipaddress.getSockAddr());

    int rc = ::connect(m_socket_fd, remote_addr, sizeof(struct sockaddr_in));

    m_remote_address = ipaddress;
    if(rc != 0) {
        switch (errno) {
        case EINPROGRESS:
            return;
            break;

        default:
            throw TcpSocketException("Failed to connect", errno);
            break;
        }
    }


}



void TcpSocket::bind(const IpAddress &ipaddress)
{
    const struct sockaddr * remote_addr = (const struct sockaddr *) (ipaddress.getSockAddr());

    if(::bind(m_socket_fd, remote_addr, sizeof(struct sockaddr_in)) < 0) {
        throw TcpSocketException("Failed to bind", errno);
    }
}



void TcpSocket::listen()
{
    if(m_listening)
        return;

    if(::listen(m_socket_fd, TCP_SOCKET_LISTEN_BACKLOG) < 0) {
        throw TcpSocketException("Failed to listen", errno);
    }

    m_listening = true;
}



TcpSocket * TcpSocket::accept()
{
    struct sockaddr_in remote_addr;
    socklen_t addrlen;

    int new_socket_fd = ::accept(m_socket_fd, (struct sockaddr *)&remote_addr, &addrlen);

    if(new_socket_fd < 0) {
        throw TcpSocketException("Failed to accept", errno);
    }

    IpAddress remore_ip;
    remore_ip.setIpAddress(remote_addr, addrlen);

    TcpSocket * accepted_conn = new TcpSocket(new_socket_fd, remore_ip);

    return accepted_conn;
}



void TcpSocket::close()
{
    ::close(m_socket_fd);
    m_listening = false;
}



int TcpSocket::send(std::string data)
{
    int bytes_sent = ::write(m_socket_fd, data.c_str(), data.size());

    if(bytes_sent < 0) {
        switch (errno) {
        case EWOULDBLOCK:
            throw TcpSocketWouldBlock();
            break;

        default:
            throw TcpSocketException("Failed to send", errno);
            break;
        }
    }

    return bytes_sent;
}



std::string TcpSocket::receive(int maxlen)
{
    char buffer[TCP_SOCKET_RECEIVE_BUFFER_SIZE];

    int max = (maxlen > 0) ? maxlen : TCP_SOCKET_RECEIVE_BUFFER_SIZE;

    int bytes_received = ::read(m_socket_fd, buffer, max);

    if(bytes_received < 0) {
        switch (errno) {
        case EWOULDBLOCK:
            throw TcpSocketWouldBlock();
            break;

        default:
            throw TcpSocketException("Failed to receive", errno);
            break;
        }
    }

    return std::string(buffer, bytes_received);
}



void TcpSocket::setNonBlockingMode() {
    int flags;

    // Get old flags
    if ((flags = fcntl(m_socket_fd, F_GETFL, 0)) < 0) {
        throw TcpSocketException("Failed to get old flags", errno);
    }

    // Set non-blocking
    if (fcntl(m_socket_fd, F_SETFL, flags | O_NONBLOCK) < 0) {
        throw TcpSocketException("Failed to set non-blocking mode", errno);
    }
}


void TcpSocket::setBlockingMode() {
    int flags;

    // Get old flags
    if ((flags = fcntl(m_socket_fd, F_GETFL, 0)) < 0) {
        throw TcpSocketException("Failed to get old flags", errno);
    }

    // Set non-blocking
    if (fcntl(m_socket_fd, F_SETFL, flags & ~O_NONBLOCK) < 0) {
        throw TcpSocketException("Failed to set non-blocking mode", errno);
    }
}

