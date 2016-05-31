#include <gtest/gtest.h>
#include <iostream>

#include <ipaddress.h>
#include <eventmanager.h>
#include <tcplistener.h>
#include <tcpconnection.h>
#include <interfaces/itcplistenerlistener.h>
#include <string.h>


class ConnectTest : public ::testing::Test, public ITcpConnectionListener {
protected:
    EventManager m_evmanager;

public:

    void testConnect() {
        try {
            IpAddress addr("127.0.0.1", 80);

            TcpConnection conn(addr);
            conn.setEventManager(&m_evmanager);
            conn.setListener(this);

            conn.open();
            m_evmanager.execute();
        }
        catch(Exception &e) {
            std::cout << e.description() << std::endl;
            FAIL();
        }
    }


    void testSocket() {

    }

    virtual void onOpened() {
        std::cout << "Connected!" << std::endl;
    }

    virtual void onClosed() {
        m_evmanager.terminate();
    }

    virtual void onReceived(std::string data) {
        std::cout << data << std::endl;
    }

};



TEST_F(ConnectTest, ConnectSomewhere) {
    testSocket();
}


