#ifndef TCPSOCKET_H
#define TCPSOCKET_H


#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <string>


#include "exceptions/tcpsocketexception.h"
#include "ipaddress.h"


#define TCP_SOCKET_LISTEN_BACKLOG 100
#define TCP_SOCKET_RECEIVE_BUFFER_SIZE 1024


class TcpSocket {
private:
    int         m_socket_fd;            ///< Socket file descriptor
    IpAddress   m_remote_address;       ///< Peer address
    bool        m_listening;            ///< Flag indicating that socket is in listening mode
    bool        m_blocking;             ///< Flag indicatong that socket is in blocking mode
    
public:
    TcpSocket();


    /**
     * @brief Wrap existing socket descriptor with convenient interface
     * @param socket_fd Socke file descriptor
     * @param remote_addr Peer address
     */
    TcpSocket(int socket_fd, const IpAddress &remote_addr);


    virtual ~TcpSocket();
    


    /**
     * @brief Set IO mode for socket
     * @param is_blocking true - socket is set in blocking mode
     *                    false - socket is set in non-blocking mode
     */
    void setBlocking(bool is_blocking);



    /**
     * @brief Set file descriptor to work with
     * <p>
     * Closes the old one
     * @param socket_fd New socket descriptor
     */
    void setSocketDescriptor(int socket_fd);



    /**
     * @brief Get file descriptor of this socket.
     * @return Socket file descriptor
     */
    int getSocketDescriptor();



    /**
     * @brief Check if socket is in listening mode
     * @return true if yes
     */
    bool isListening();



    /**
     * @brief Get remote address
     * @return Peer IP address
     */
    IpAddress remoteAddress();



    /**
     * @brief Connect to remote IP
     * @param ipaddress address to connect to
     */
    void connect(const IpAddress& ipaddress);



    /**
     * @brief Bind socket on a local address
     * @param ipaddress Address to bind socket
     */
    void bind(const IpAddress& ipaddress);



    /**
     * @brief Switch socket into listening state.
     */
    void listen();



    /**
     * @brief Accept pending connection.
     * @return Opened connection to a client
     */
    TcpSocket * accept();



    /**
     * @brief Close socket
     */
    void close();



    /**
     * @brief Send data
     * @param data Data to send
     * @return Number of bytes sent
     */
    int send(std::string data);



    /**
     * @brief Receive data from socket
     * @param maxlen Maximum bytes to receive from peer. -1 for max;
     * @return Data received from peer
     */
    std::string receive(int maxlen = -1);


    
private:
    /**
     * @brief Switch socket into non-blocking mode
     */
    void setNonBlockingMode();


    /**
     * @brief Switch socket into blocking mode
     */
    void setBlockingMode();


};


#endif
