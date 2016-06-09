#include <gtest/gtest.h>
#include <iostream>

#include <ipaddress.h>
#include <eventmanager.h>
#include <tcplistener.h>
#include <tcpconnection.h>
#include <interfaces/itcplistenerlistener.h>
#include <string.h>



class AsyncConnectGoogle : public ::testing::Test, public ITcpConnectionListener {
protected:
    EventManager *  m_evmanager;
    TcpConnection * m_conn;

public:
    void SetUp() {
        // google.com
        IpAddress addr("178.45.249.237", 80);

        m_evmanager = new EventManager();
        m_conn = new TcpConnection(addr);
        m_conn->setEventManager(m_evmanager);
        m_conn->setListener(this);
    }

    void TearDown() {
        delete m_evmanager;
        delete m_conn;
    }

    void testRequest() {
        try {
            m_conn->open();
            m_evmanager->execute();
        }
        catch(Exception &e) {
            FAIL() << e.description();
        }
    }

    virtual void onOpened() {
        m_conn->close();
        SUCCEED();
    }

    virtual void onClosed() {
        m_evmanager->terminate();
    }

    virtual void onReceived(std::string data) {
        FAIL() << "No data should arrive";
    }

};

TEST_F(AsyncConnectGoogle, Connect) {
    FAIL();
//    testRequest();
}


class AsyncRequestGoogle : public ::testing::Test, public ITcpConnectionListener {
protected:
    EventManager *  m_evmanager;
    TcpConnection * m_conn;

public:
    void SetUp() {
        // google.com
        IpAddress addr("178.45.249.237", 80);

        m_evmanager = new EventManager();
        m_conn = new TcpConnection(addr);
        m_conn->setEventManager(m_evmanager);
        m_conn->setListener(this);
    }

    void TearDown() {
        delete m_evmanager;
        delete m_conn;
    }

    void testRequest() {
        try {
            m_conn->open();
            m_evmanager->execute();
        }
        catch(Exception &e) {
            FAIL() << e.description();
        }
    }

    virtual void onOpened() {
        m_conn->send("GET / HTTP/1.0\r\n\r\n");
    }

    virtual void onClosed() {
        m_evmanager->terminate();
        SUCCEED();
    }

    virtual void onReceived(std::string data) {
        m_conn->close();
        if(data.size() <= 0)
            FAIL() << "No datareceived";
    }

};



TEST_F(AsyncRequestGoogle, Request) {
    FAIL();
//    testRequest();
}


