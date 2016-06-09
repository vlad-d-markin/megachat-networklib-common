#include <gtest/gtest.h>
#include <string>

#include <eventmanager.h>
#include <tcplistener.h>
#include <tcpconnection.h>
#include <tcpsocket.h>
#include <interfaces/itcpconnectionlistener.h>
#include <interfaces/itcplistenerlistener.h>


class Strategy;

class ITestHelper {
public:
    virtual void setStrategy(Strategy * strategy) = 0;
    virtual TcpConnection * getClient() = 0;
    virtual TcpConnection * getServer() = 0;
    virtual void finishTest() = 0;
};




class Strategy {
protected:
    ITestHelper * m_test_helper;

public:
    Strategy(ITestHelper * helper) : m_test_helper(helper) {}

    virtual void onClientOpened() {
        FAIL() << "onClientOpened()";
        m_test_helper->finishTest();
    }

    virtual void onClientClosed(){
        FAIL() << "onClientClosed()";
        m_test_helper->finishTest();
    }

    virtual void onClientReceived(std::string data) {
        FAIL() << "onClientReceived() (" + data + ")";
        m_test_helper->finishTest();
    }

    virtual void onServerOpened() {
        FAIL() << "onServerOpened()";
        m_test_helper->finishTest();
    }

    virtual void onServerClosed() {
        FAIL() << "onServerClosed()";
        m_test_helper->finishTest();
    }

    virtual void onServerReceived(std::string data) {
        FAIL() << "onServerReceived() (" + data + ")";
        m_test_helper->finishTest();
    }
};




class CloseStrategy : public Strategy {
private:
    bool m_client_closed;
    bool m_server_closed;

public:
    CloseStrategy(ITestHelper * helper) : Strategy(helper),
        m_client_closed(false), m_server_closed(false) {}

    virtual void onClientClosed() {
        m_client_closed = true;

        if(m_client_closed && m_server_closed) {
            m_test_helper->finishTest();
            SUCCEED();
        }
    }


    virtual void onServerClosed() {
        m_server_closed = true;

        if(m_client_closed && m_server_closed) {
            m_test_helper->finishTest();
            SUCCEED();
        }
    }
};


class ClienReceivedStrategy : public Strategy {
public:
    ClienReceivedStrategy(ITestHelper * helper) : Strategy(helper) {}

    virtual void onClientReceived(std::string data) {
        ASSERT_EQ(data, "test2");
        m_test_helper->setStrategy(new CloseStrategy(m_test_helper));
        m_test_helper->getClient()->close();
    }
};




class ServerReceivedStragety : public Strategy {
public:
    ServerReceivedStragety(ITestHelper * helper) : Strategy(helper) {}

    virtual void onServerReceived(std::string data) {
        ASSERT_EQ(data, "test1");
        m_test_helper->getServer()->send("test2");
        m_test_helper->setStrategy(new ClienReceivedStrategy(m_test_helper));
    }
};




class OpenConnectionStrategy : public Strategy {
public:
    OpenConnectionStrategy(ITestHelper * helper) : Strategy(helper) {}

    virtual void onClientOpened() {
        m_test_helper->getClient()->send("test1");
        m_test_helper->setStrategy(new ServerReceivedStragety(m_test_helper));
    }
};


class ICurrentStrategyProvider {
public:
    virtual Strategy * getStrategy() = 0;
};




class ClientTcpListener : public ITcpConnectionListener {
private:
    ICurrentStrategyProvider * m_strategy_provider;

public:
    ClientTcpListener(ICurrentStrategyProvider * provider) : m_strategy_provider(provider) {}

    void onOpened(){
        m_strategy_provider->getStrategy()->onClientOpened();
    }

    void onClosed() {
        m_strategy_provider->getStrategy()->onClientClosed();
    }

    void onReceived(std::string data) {
        m_strategy_provider->getStrategy()->onClientReceived(data);
    }
};




class ServerTcpListener : public ITcpConnectionListener {
private:
    ICurrentStrategyProvider * m_strategy_provider;

public:
    ServerTcpListener(ICurrentStrategyProvider * provider) : m_strategy_provider(provider) {}

    void onOpened(){
        m_strategy_provider->getStrategy()->onServerOpened();
    }

    void onClosed() {
        m_strategy_provider->getStrategy()->onServerClosed();
    }

    void onReceived(std::string data) {
        m_strategy_provider->getStrategy()->onServerReceived(data);
    }
};




class TestHelper : public ICurrentStrategyProvider,
        public ITcpListenerListener, public ::testing::Test,
        public ITestHelper  {
private:
    TcpConnection * m_client;
    TcpConnection * m_server;
    TcpListener * m_listener;
    EventManager * m_evmanager;

    Strategy * m_strategy;

    ClientTcpListener * m_client_listener;
    ServerTcpListener * m_server_listener;


public:

    TestHelper() {

    }

    void runTest() {
        m_strategy = new OpenConnectionStrategy(this);

        m_client_listener = new ClientTcpListener(this);
        m_server_listener = new ServerTcpListener(this);

        m_evmanager = new EventManager();
        m_client = new TcpConnection(IpAddress("127.0.0.1", 9999));
        m_listener = new TcpListener();

        m_listener->listen(9999);
        m_listener->setListener(this);

        m_client->setEventManager(m_evmanager);
        m_client->setListener(m_client_listener);
        m_client->open();

        m_evmanager->registerClient(m_listener);
        m_evmanager->registerClient(m_client);

        m_evmanager->execute();

        delete m_strategy;

        delete m_client_listener;
        delete m_server_listener;

        delete m_client;
        delete m_server;
        delete m_listener;
        delete m_evmanager;
    }


    virtual void finishTest() {
        m_evmanager->terminate();
    }


    virtual Strategy * getStrategy() {
        return m_strategy;
    }


    virtual void setStrategy(Strategy *strategy) {
        if(m_strategy != 0)
            delete m_strategy;

        m_strategy = strategy;
    }

    virtual TcpConnection * getClient() {
        return m_client;
    }

    virtual TcpConnection * getServer() {
        return m_server;
    }

    virtual void onAccepted(TcpSocket *socket) {
        m_server = new TcpConnection(socket);
        m_server->setEventManager(m_evmanager);
        m_server->setListener(m_server_listener);
        m_evmanager->registerClient(m_server);
    }


    virtual void onClosed() {
        // Clled from TcpListener
    }

};




TEST_F(TestHelper, ConnTest) {
    try {
    runTest();
    }
    catch(Exception &e) {
        FAIL() << e.description();
    }
}




