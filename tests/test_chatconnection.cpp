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

    // Login Ack
    char m_login_ack_code;

    // Message out

    // Message Out Ack


    void clear() {
        m_packet_code = -1;

        m_username.clear();
        m_password.clear();

        m_login_ack_code = -1;
    }

    virtual void onOpened() {}

    virtual void onClosed() {}

    virtual void onLogin(std::string username, std::string password)
    {
        m_packet_code = ChatPacketBuilder::LOGIN;
        m_username = username;
        m_password = password;
    }


    virtual void onLoginAck(char code)
    {
        m_packet_code = ChatPacketBuilder::LOGIN_ACK;
        m_login_ack_code = code;
    }


    virtual void onLogout()
    {
        m_packet_code = ChatPacketBuilder::LOGOUT;
    }


    virtual void onLogoutAck()
    {
        m_packet_code = ChatPacketBuilder::LOGOUT_ACK;
    }


    virtual void onMessageOut(std::string recipient, int message_id, std::string message) {}
    virtual void onMessageOutAck(int message_id, char code) {}
    virtual void onMessageIn(std::string sender, int message_id, std::string message) {}
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

protected:
    virtual void SetUp() {
        m_chat_connection.setListener(&m_chat_connection_listener_spy);
        m_byte_connection_spy.clear();
        m_chat_connection_listener_spy.clear();
    }

public:
    TestChatConnection() :
        m_chat_connection(&m_byte_connection_spy)
    {
        m_chat_connection.setListener(&m_chat_connection_listener_spy);
        m_byte_connection_spy.clear();
        m_chat_connection_listener_spy.clear();
    }

    /////////////////////////////////////////
    // Test packet sending
    /////////////////////////////////////////

    void testSendLogin()
    {
        m_chat_connection.sendLogin("user", "pass");

        ASSERT_EQ(m_byte_connection_spy.m_data, std::string("\x0\x0\xF\x0\x4user\x0\x4pass", 15));
    }

    void testSendLoginAck()
    {
        m_chat_connection.sendLoginAck(1);

        ASSERT_EQ(m_byte_connection_spy.m_data, std::string("\x1\x0\x4\x1", 4));
    }

    void testSendLogout()
    {
        m_chat_connection.sendLogout();

        ASSERT_EQ(m_byte_connection_spy.m_data, std::string("\x2\x0\x3", 3));
    }

    void testSendLogoutAck()
    {
        m_chat_connection.sendLogoutAck();

        ASSERT_EQ(m_byte_connection_spy.m_data, std::string("\x3\x0\x3", 3));
    }


    /////////////////////////////////////////
    // Test packet receiving
    /////////////////////////////////////////

    void testReceivedLogin() {
        m_chat_connection_listener_spy.clear();
        m_chat_connection.onReceived(std::string("\x0\x0\xF\x0\x4user\x0\x4pass", 15));

        ASSERT_EQ(m_chat_connection_listener_spy.m_packet_code, ChatPacketBuilder::LOGIN);
        ASSERT_EQ(m_chat_connection_listener_spy.m_username, "user");
        ASSERT_EQ(m_chat_connection_listener_spy.m_password, "pass");
    }

    void testReceivedLoginAck() {
        m_chat_connection_listener_spy.clear();
        m_chat_connection.onReceived(std::string("\x1\x0\x4\x2", 4));

        ASSERT_EQ(m_chat_connection_listener_spy.m_packet_code, ChatPacketBuilder::LOGIN_ACK);
        ASSERT_EQ(m_chat_connection_listener_spy.m_login_ack_code, 2);
    }

    void testReceivedLogout() {
        m_chat_connection_listener_spy.clear();
        m_chat_connection.onReceived(std::string("\x2\x0\x3", 3));

        ASSERT_EQ(m_chat_connection_listener_spy.m_packet_code, ChatPacketBuilder::LOGOUT);
    }
};




// Run tests

TEST_F(TestChatConnection, SendLogin) { testSendLogin(); }
TEST_F(TestChatConnection, SendLoginAck) { testSendLoginAck(); }
TEST_F(TestChatConnection, SendLogout) { testSendLogout(); }
TEST_F(TestChatConnection, SendLogoutAck) { testSendLogoutAck(); }



TEST_F(TestChatConnection, ReceivedLogin) { testReceivedLogin(); }
TEST_F(TestChatConnection, ReceivedLoginAck) { testReceivedLoginAck(); }
TEST_F(TestChatConnection, ReceivedLogout) { testReceivedLogout(); }




