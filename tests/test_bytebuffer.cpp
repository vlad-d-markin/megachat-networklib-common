#include <gtest/gtest.h>
#include <bytebuffer.h>


#include <iostream>



TEST(ByteBufferTest, CreateEmpty)
{
    ByteBuffer bb;
    ASSERT_EQ(bb.size(), 0);
}



TEST(ByteBufferTest, CreateFrowRaw)
{
    char raw_data[] = "initial-data";
    ByteBuffer bb((u_int8_t *) raw_data, strlen(raw_data));


    ASSERT_EQ(strlen(raw_data), bb.size());
    ASSERT_TRUE(memcmp(raw_data, bb.data(), bb.size()) == 0);
}



TEST(ByteBufferTest, CreateFromStdStr)
{
    std::string initial_string = "std string";
    ByteBuffer bb(initial_string);


    ASSERT_EQ(initial_string.length(), bb.size());
    ASSERT_TRUE(memcmp(initial_string.c_str(), bb.data(), bb.size()) == 0);
}



TEST(ByteBufferTest, CreateFromByteBuffer)
{
    ByteBuffer initial_bb("test-value");
    ByteBuffer bb(initial_bb);


    ASSERT_EQ(initial_bb.size(), bb.size());
    ASSERT_TRUE(memcmp(initial_bb.data(), bb.data(), bb.size()) == 0);
}



TEST(ByteBufferTest, AppendRawString)
{
    ByteBuffer bb;

    char raw_data[] = "test_raw_content";
    bb.append((u_int8_t *)raw_data, strlen(raw_data));

    ASSERT_EQ(strlen(raw_data), bb.size());
    ASSERT_TRUE(memcmp(raw_data, bb.data(), bb.size()) == 0);
}



TEST(ByteBufferTest, AppendRawData)
{
    ByteBuffer bb;

    u_int8_t raw_data[] = {10, 21, 13, 123, 45, 66};
    bb.append(raw_data, sizeof(raw_data));

    ASSERT_EQ(sizeof(raw_data), bb.size());
    ASSERT_TRUE(memcmp(raw_data, bb.data(), bb.size()) == 0);
}



TEST(ByteBufferTest, AppendStdStr)
{
    ByteBuffer bb;

    std::string test_string = "mega-test";
    bb.append(test_string);

    ASSERT_TRUE(memcmp(test_string.c_str(), bb.data(), bb.size()) == 0);
}



TEST(ByteBufferTest, AppendByteBuffer)
{
    ByteBuffer bb;

    ByteBuffer another_buffer;
    another_buffer.append("test-data");

    bb.append(another_buffer);

    ASSERT_TRUE(memcmp(another_buffer.data(), bb.data(), bb.size()) == 0);
}



TEST(ByteBufferTest, ToStringConvertion)
{
    std::string test_string = "some_text_here";
    ByteBuffer bb(test_string);

    ASSERT_EQ(test_string, bb.toString());
}



TEST(ByteBufferTest, CutPart)
{
    try {
        ByteBuffer bb1("test_string_cut");
        ByteBuffer bb2("cut_test_cut");
        ByteBuffer bb3("cut_test");


        ASSERT_EQ(bb1.cut(0, 11), ByteBuffer("test_string"));
        ASSERT_EQ(bb2.cut(4, 8), ByteBuffer("test"));
        ASSERT_EQ(bb3.cut(4), ByteBuffer("test"));
    }
    catch(Exception &e) {
        FAIL() << e.description();
    }
}



TEST(ByteBufferTest, RemoveFront)
{
    ByteBuffer bb("cut_test_string");

    bb.removeFront(4);

    ASSERT_EQ(bb, ByteBuffer("test_string"));
}



TEST(ByteBufferTest, RemoveRear)
{
    ByteBuffer bb("test_string_cut");

    bb.removeRear(4);

    ASSERT_EQ(bb, ByteBuffer("test_string"));
}




TEST(ByteBufferTest, EqualOperator)
{
    ByteBuffer a("test string");
    ByteBuffer b("test string");

    ASSERT_EQ(a, b);
}



TEST(ByteBufferTest, AppendOperator)
{
    ByteBuffer to_append("some text");
    ByteBuffer bb;

    bb += to_append;

    ASSERT_EQ(to_append, bb);
}



TEST(ByteBufferTest, SumOperator)
{
    ByteBuffer aa("hello");
    ByteBuffer bb("world");

    ByteBuffer valid("helloworld");

    ASSERT_EQ(aa + bb, valid);
}

