#include <gtest/gtest.h>
#include <string>

#include <chatpacketbuilder.h>
#include <bytebuffer.h>


TEST(PacketBuilding, BuildLogin) {
    ByteBuffer test_packet;
    u_int8_t valid_packet[] = "\x0\x0\xF\x0\x4user\x0\x4pass";

    test_packet = ChatPacketBuilder::buildLogin("user", "pass");

    ASSERT_EQ(test_packet.size(), sizeof(valid_packet) - 1);
    ASSERT_TRUE(memcmp(test_packet.data(), valid_packet, test_packet.size()));
}



TEST(PacketBuilding, BuildLoginAck) {
    ByteBuffer test_packet;
    u_int8_t valid_packet[] = "\x1\x0\x4\x1";

    test_packet = ChatPacketBuilder::buildLoginAck(1);

    ASSERT_EQ(test_packet.size(), sizeof(valid_packet) - 1);
    ASSERT_TRUE(memcmp(test_packet.data(), valid_packet, test_packet.size()));
}



TEST(PacketBuilding, BuildLogout) {
    ByteBuffer test_packet;
    u_int8_t valid_packet[] = "\x2\x0\x3";

    test_packet = ChatPacketBuilder::buildLogout();

    ASSERT_EQ(test_packet.size(), sizeof(valid_packet) - 1);
    ASSERT_TRUE(memcmp(test_packet.data(), valid_packet, test_packet.size()));
}



TEST(PacketBuilding, BuildLogoutAck) {
    ByteBuffer test_packet;
    u_int8_t valid_packet[] = "\x3\x0\x3";

    test_packet = ChatPacketBuilder::buildLogoutAck();

    ASSERT_EQ(test_packet.size(), sizeof(valid_packet) - 1);
    ASSERT_TRUE(memcmp(test_packet.data(), valid_packet, test_packet.size()));
}



TEST(PacketBuilding, BuildMessageOut) {
    ByteBuffer test_packet;
    // 1 + 2 + 2 + rec + 4 + 2 + msg
    u_int8_t valid_packet[] = "\x4\x0\xB\x0\x4user\x0\x0\x0\x2A\x0\x2hi";

    test_packet = ChatPacketBuilder::buildMessageOut("user", 42, "hi");

    ASSERT_EQ(test_packet.size(), sizeof(valid_packet) - 1);
    ASSERT_TRUE(memcmp(test_packet.data(), valid_packet, test_packet.size()));
}



TEST(PacketBuilding, BuildMessageOutAck) {
    ByteBuffer test_packet;
    // 1 + 2 + 4 + 1
    u_int8_t valid_packet[] = "\x5\x0\x8\x0\x0\x0\x4D\x1";

    test_packet = ChatPacketBuilder::buildMessageOutAck(77, 1);

    ASSERT_EQ(test_packet.size(), sizeof(valid_packet) - 1);
    ASSERT_TRUE(memcmp(test_packet.data(), valid_packet, test_packet.size()));
}
