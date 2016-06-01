#include <gtest/gtest.h>
#include <string>

#include <chatpacketbuilder.h>


TEST(PacketBuilding, BuildLogin) {
    std::string packet;


    ASSERT_EQ(packet, "\0\1\2\3");
}
