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



TEST(PacketBuilding, BuildMessageIn) {
    ByteBuffer test_packet;
    // 1 + 2 + 2 + send + 4 + 2 + msg = 11 + 4 + 2 = 17
    u_int8_t valid_packet[] = "\x6\x0\x11\x0\x4\jack\x0\x0\x0\x58\x0\x2go";

    test_packet = ChatPacketBuilder::buildMessageIn("jack", 88, "go");

    ASSERT_EQ(test_packet.size(), sizeof(valid_packet) - 1);
    ASSERT_TRUE(memcmp(test_packet.data(), valid_packet, test_packet.size()));
}



TEST(PacketBuilding, BuildMessageInAck) {
    ByteBuffer test_packet;
    // 1 + 2 + 4 + 1
    u_int8_t valid_packet[] = "\x7\x0\x8\x0\x0\x0\x63\x1";

    test_packet = ChatPacketBuilder::buildMessageInAck(99, 1);

    ASSERT_EQ(test_packet.size(), sizeof(valid_packet) - 1);
    ASSERT_TRUE(memcmp(test_packet.data(), valid_packet, test_packet.size()));
}



TEST(PacketBuilding, BuildContactListRequest) {
    ByteBuffer test_packet;
    // 1 + 2 + 4 + 1
    u_int8_t valid_packet[] = "\x8\x0\x3";

    test_packet = ChatPacketBuilder::buildContactListRequest();

    ASSERT_EQ(test_packet.size(), sizeof(valid_packet) - 1);
    ASSERT_TRUE(memcmp(test_packet.data(), valid_packet, test_packet.size()));
}



TEST(PacketBuilding, BuildContactListResponse) {
    ByteBuffer test_packet;
    // 1 + 2 + 2 + (2 + uname + 1) * ncont = 5 + 2 * ( 3 + 4 )
    u_int8_t valid_packet[] = "\x9\x0\x13\x0\x2\x0\x4user\x1\x0\x4jack\x0";


    std::vector<User> contacts;
    contacts.push_back(User {"user", 1});
    contacts.push_back(User {"jack", 0});

    test_packet = ChatPacketBuilder::buildContactListResponse(contacts);

    ASSERT_EQ(test_packet.size(), sizeof(valid_packet) - 1);
    ASSERT_TRUE(memcmp(test_packet.data(), valid_packet, test_packet.size()));
}



TEST(PacketBuilding, BuildPresence) {
    ByteBuffer test_packet;
    // 1 + 2 + user + 1
    u_int8_t valid_packet[] = "\xA\x0\x8user\x1";

    test_packet = ChatPacketBuilder::buildPresence("user", 1);

    ASSERT_EQ(test_packet.size(), sizeof(valid_packet) - 1);
    ASSERT_TRUE(memcmp(test_packet.data(), valid_packet, test_packet.size()));
}



TEST(PacketBuilding, BuildPresenceAck) {
    ByteBuffer test_packet;
    // 1 + 2 + user
    u_int8_t valid_packet[] = "\xB\x0\x6\bob";

    test_packet = ChatPacketBuilder::buildPresenceAck("bob");

    ASSERT_EQ(test_packet.size(), sizeof(valid_packet) - 1);
    ASSERT_TRUE(memcmp(test_packet.data(), valid_packet, test_packet.size()));
}



TEST(PacketBuilding, BuildKeepAlive) {
    ByteBuffer test_packet;
    // 1 + 2 + 1
    u_int8_t valid_packet[] = "\xC\x0\x3";

    test_packet = ChatPacketBuilder::buildKeepAlive();

    ASSERT_EQ(test_packet.size(), sizeof(valid_packet) - 1);
    ASSERT_TRUE(memcmp(test_packet.data(), valid_packet, test_packet.size()));
}



TEST(PacketBuilding, BuildKeepAliveAck) {
    ByteBuffer test_packet;
    // 1 + 2 + 1
    u_int8_t valid_packet[] = "\xD\x0\x3";

    test_packet = ChatPacketBuilder::buildKeepAliveAck();

    ASSERT_EQ(test_packet.size(), sizeof(valid_packet) - 1);
    ASSERT_TRUE(memcmp(test_packet.data(), valid_packet, test_packet.size()));
}
