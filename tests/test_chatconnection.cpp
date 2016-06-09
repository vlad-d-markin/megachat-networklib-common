#include <gtest/gtest.h>


#include <chatconnection.h>
#include <interfaces/ichatconnectionlistener.h>
#include <interfaces/ibyteconnection.h>
#include <chatpacketbuilder.h>


class ByteConnectionSpy : public IByteConnection {
public:
    bool m_opened;
    bool m_closed;
    std::string m_data;


    virtual void open() {
        m_opened = true;
    }


    virtual void close() {
        m_closed = true;
    }


    virtual void send(std::string data) {
        m_data += data;
    }


    void clear() {
        m_opened = false;
        m_closed = false;
        m_data.clear();
    }
};



class ChatConnectionListenerSpy : public IChatConnectionListener {
public:
    int m_packet_code;

    // Login
    std::string m_username;
    std::string m_password;

    //


    void clear() {
        m_packet_code = -1;

        m_username.clear();
        m_password.clear();
    }

    virtual void onOpened() {}

    virtual void onClosed() {}

    virtual void onLogin(std::string username, std::string password)
    {
        m_packet_code = ChatPacketBuilder::LOGIN;
        m_username = username;
        m_password = password;
    }


    virtual void onLoginAck() {}
    virtual void onLogout() {}
    virtual void onLogoutAck() {}
    virtual void onMessageOut(int message_id, std::string sender, std::string recipient, std::string message) {}
    virtual void onMessageOutAck(int message_id, char code) {}
    virtual void onMessageIn(int message_id, std::string sender, std::string recipient, std::string message) {}
    virtual void onMessageInAck(int message_id, char code) {}
    virtual void onContactListRequest() {}
    virtual void onContactListResponse(std::vector<std::string> contacts) {}
    virtual void onPresence(std::string username, char status) {}
    virtual void onPresenceAck(std::string username) {}
    virtual void onKeepAlive() {}
    virtual void onKeepAliveAck() {}
};




class TestChatConnection : public ::testing::Test {
private:
    ByteConnectionSpy           m_byte_connection_spy;
    ChatConnectionListenerSpy   m_chat_connection_listener_spy;
    ChatConnection              m_chat_connection;

public:
    TestChatConnection() :
        m_chat_connection(&m_byte_connection_spy)
    {
        m_chat_connection.setListener(&m_chat_connection_listener_spy);
    }


    void testSendLogin() {
        m_byte_connection_spy.clear();
        m_chat_connection.sendLogin("user", "pass");

        ASSERT_EQ(m_byte_connection_spy.m_data, std::string("\x0\x0\xF\x0\x4user\x0\x4pass", 15));
    }


    void testReceivedLogin() {
        m_chat_connection_listener_spy.clear();
        m_chat_connection.onReceived(std::string("\x0\x0\xF\x0\x4user\x0\x4pass", 15));

        ASSERT_EQ(m_chat_connection_listener_spy.m_packet_code, ChatPacketBuilder::LOGIN);
        ASSERT_EQ(m_chat_connection_listener_spy.m_username, "user");
        ASSERT_EQ(m_chat_connection_listener_spy.m_password, "pass");
    }
};



TEST_F(TestChatConnection, SendLogin)
{
    testSendLogin();
}


TEST_F(TestChatConnection, ReceivedLogin)
{
    testReceivedLogin();
}


