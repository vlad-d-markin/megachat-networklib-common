#include <gtest/gtest.h>
#include <string>

#include <chatpacketbuilder.h>
#include <bytebuffer.h>


TEST(PacketBuilding, BuildLogin) {
    ByteBuffer packet;

    packet = ChatPacketBuilder::buildLogin("user", "password");

    std::cerr << packet.toString() << std::endl;
    std::cerr << "\x00\x00\x11\x00\x04user\x00\x08password" << std::endl;

    ASSERT_EQ(packet.toString(), "\0\0\0\0\x13\0\0\0\x4user\0\x8password");
}
