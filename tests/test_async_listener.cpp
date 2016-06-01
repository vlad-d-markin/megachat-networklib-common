#include <gtest/gtest.h>
#include <string>

#include <eventmanager.h>
#include <tcplistener.h>
#include <tcpconnection.h>
#include <tcpsocket.h>
#include <interfaces/itcpconnectionlistener.h>
#include <interfaces/itcplistenerlistener.h>


class TestHelper;

class BaseTestState {
protected:
    TestHelper * m_helper;
public:
    BaseTestState(TestHelper * helper) : m_helper(helper) {}

    virtual void onServerAccepted(TcpSocket * socket) { FAIL() << "State received wrong event"; }
    virtual void onServerReceived(ByteBuffer data) { FAIL() << "State received wrong event"; }
    virtual void onServerClosed() { FAIL() << "State received wrong event"; }

    virtual void onClientOpened() { FAIL() << "State received wrong event"; }
    virtual void onClientReceived(ByteBuffer data) { FAIL() << "State received wrong event"; }
    virtual void onClientClosed() { FAIL() << "State received wrong event"; }
};


class WaitingForClientState;
class WaitingForClientRequestState;


class WaitingForClientState : public BaseTestState {
public:
    WaitingForClientState(TestHelper * helper) : BaseTestState(helper) {}

    void onServerAccepted(TcpSocket * socket)
    {
//        std::cerr << "Accepted new client" << std::endl;
//        delete m_helper->m_state;
//        m_helper->m_state = new WaitingForClientRequestState(m_helper);
    }


    void onServerReceived(ByteBuffer data) { FAIL() << "State received wrong event"; }
    void onServerClosed() { FAIL() << "State received wrong event"; }
    void onClientOpened() {  }
    void onClientReceived(ByteBuffer data) { FAIL() << "State received wrong event"; }
    void onClientClosed() { FAIL() << "State received wrong event"; }
};


class WaitingForClientRequestState : public BaseTestState {
public:
    WaitingForClientRequestState(TestHelper * helper) : BaseTestState(helper) {}

    void onServerAccepted(TcpSocket * socket) { FAIL() << "State received wrong event"; }


    void onServerReceived(ByteBuffer data) { FAIL() << "State received wrong event"; }
    void onServerClosed() { FAIL() << "State received wrong event"; }
    void onClientOpened() {  }
    void onClientReceived(ByteBuffer data) { FAIL() << "State received wrong event"; }
    void onClientClosed() { FAIL() << "State received wrong event"; }
};



class TestHelper : public testing::Test {
public:
    BaseTestState * m_state;

    EventManager * m_evmanager;
    TcpConnection * m_connection;
    TcpListener *   m_listener;


    // Clitent side listener redirects all events to helper
    class ClientSideListener : public ITcpConnectionListener {
        BaseTestState ** m_state;
    public:
        ClientSideListener(BaseTestState ** state) : m_state(state) {}

        virtual void onOpened() {
            (*m_state)->onClientOpened();
        }

        virtual void onClosed() {
            (*m_state)->onClientClosed();
        }

        virtual void onReceived(ByteBuffer data) {
            (*m_state)->onClientReceived(data);
        }
    };

    // Server side listener redirects all events to helper
    class ServerSideListener : public ITcpListenerListener {
        BaseTestState ** m_state;
    public:
        ServerSideListener(BaseTestState ** state) : m_state(state) {}

        virtual void onAccepted(TcpSocket *socket) {
            (*m_state)->onServerAccepted(socket);
        }

        virtual void onClosed() {
            (*m_state)->onServerClosed();
        }

        virtual void onReceived(ByteBuffer data) {
            (*m_state)->onServerReceived(data);
        }
    };


    ClientSideListener * m_client_listener;
    ServerSideListener * m_server_listener;

    TestHelper() {
        // Setup default state that fails test
        m_state = new BaseTestState(this);

        // Listeners that redirect all events to current state
        m_server_listener = new ServerSideListener(&m_state);
        m_client_listener = new ClientSideListener(&m_state);

        // Event manager
        m_evmanager = new EventManager();

        // Server
        m_listener = new TcpListener();
        m_listener->setListener(m_server_listener);
        m_evmanager->registerClient(m_listener);

        // Client
        IpAddress addr("127.0.0.1", 9999);
        m_connection = new TcpConnection(addr);
        m_connection->setListener(m_client_listener);
        m_connection->setEventManager(m_evmanager);
    }

    void startTest() {
        try {
            m_listener->listen(9999);
            m_state = new WaitingForClientState(this);

            m_connection->open();

            m_evmanager->execute();
        }
        catch (Exception &e) {
            m_listener->close();
            FAIL() << e.description();
        }
    }

};


TEST_F(TestHelper, ConnTest) {
//    startTest();
}




