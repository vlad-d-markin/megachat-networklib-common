#include <gtest/gtest.h>
#include <ipaddress.h>


class IpAddressTest : public ::testing::Test {
protected:
    IpAddress m_test_address;

public:
    IpAddressTest() : m_test_address("127.0.0.1", 8800) {}

    void testSetIp(std::string ip)
    {
        m_test_address.setIpAddress(ip);
    }

    void testSetPort(int port) {
        m_test_address.setPort(port);
    }

    struct sockaddr_in getValidStructForLoopback() {
        struct sockaddr_in valid;
        memset(&valid, 0, sizeof(valid));

        ::inet_pton(AF_INET, "127.0.0.1", &valid);

        valid.sin_family = AF_INET;
        valid.sin_port = ::htons(800);

        return valid;
    }

    struct sockaddr_in getTestingStruct() {
        IpAddress addr("127.0.0.1", 800);
        return * addr.getSockAddr();
    }

    bool testMatch() {
        struct sockaddr_in test = getTestingStruct();
        struct sockaddr_in valid = getValidStructForLoopback();

        return memcmp(&test, &valid, sizeof(test)) == 0;
    }
};



TEST_F(IpAddressTest, TestValidationInvalidIPs) {
    ASSERT_THROW(testSetIp("666.12.56.3"),  InvalidAddressException);
    ASSERT_THROW(testSetIp(".12.56.3"),     InvalidAddressException);
    ASSERT_THROW(testSetIp("12154"),        InvalidAddressException);
    ASSERT_THROW(testSetIp("8.8.8.8."),     InvalidAddressException);
    ASSERT_THROW(testSetIp("blablds"),      InvalidAddressException);
}



TEST_F(IpAddressTest, TestValidationValidIPs) {
    ASSERT_NO_THROW(testSetIp("9.12.56.3"));
    ASSERT_NO_THROW(testSetIp("80.12.56.3"));
    ASSERT_NO_THROW(testSetIp("8.8.8.8"));
    ASSERT_NO_THROW(testSetIp("127.0.0.1"));
    ASSERT_NO_THROW(testSetIp("192.168.56.42"));
}

TEST_F(IpAddressTest, TestValidationInvalidPorts) {
    ASSERT_THROW(testSetPort(-5),     InvalidPortException);
    ASSERT_THROW(testSetPort(-9545),  InvalidPortException);
    ASSERT_THROW(testSetPort(-8599),  InvalidPortException);
}


TEST_F(IpAddressTest, TestValidationValidPorts) {
    ASSERT_NO_THROW(testSetPort(80));
    ASSERT_NO_THROW(testSetPort(8800));
    ASSERT_NO_THROW(testSetPort(7575));
}


TEST_F(IpAddressTest, TestLoopBackAddressMatch) {
    ASSERT_TRUE(testMatch());
}


