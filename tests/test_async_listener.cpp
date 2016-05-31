#include <gtest/gtest.h>
#include <string>

#include <eventmanager.h>
#include <tcplistener.h>
#include <tcpconnection.h>
#include <tcpsocket.h>


class ITestState {
public:
    virtual void onServerAccepted(TcpSocket * socket) = 0;
    virtual void onServerReceived() = 0;
    virtual void onServerClosed() = 0;

    virtual void onClientOpened() = 0;
    virtual void onClientReceived() = 0;
    virtual void onClientClosed() = 0;
};


class WaitingForClientState : public ITestState {
public:
    void onServerAccepted(TcpSocket * socket)
    {
        TcpConnection * conn = new TcpConnection(socket);
    }

    void onServerReceived() { FAIL() << "State received wrong event"; }
    void onServerClosed() { FAIL() << "State received wrong event"; }

    void onClientOpened() { FAIL() << "State received wrong event"; }
    void onClientReceived() { FAIL() << "State received wrong event"; }
    void onClientClosed() { FAIL() << "State received wrong event"; }
};
