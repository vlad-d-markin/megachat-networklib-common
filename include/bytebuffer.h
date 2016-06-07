#ifndef BYTEBUFFER_H
#define BYTEBUFFER_H

#include <vector>
#include <string>
#include <sys/types.h>
#include <string.h>


#include "exceptions/bytebufferexception.h"



class ByteBuffer {
private:
    std::vector<u_int8_t> m_data;

public:
    ByteBuffer();
    ByteBuffer(const u_int8_t * raw_data, size_t length);
    ByteBuffer(const std::string& str);
    ByteBuffer(const ByteBuffer& buffer);


    void clear();


    ByteBuffer cut(int from, int to = -1);


    ByteBuffer& removeFront(size_t bytes);
    ByteBuffer& removeRear(size_t bytes);

    ByteBuffer& setAt(size_t pos, u_int16_t word);

    ByteBuffer& set(const u_int8_t * raw_data, size_t length);
    ByteBuffer& set(const std::string& str);
    ByteBuffer& set(const ByteBuffer& buffer);


    ByteBuffer& append(const u_int8_t * raw_data, size_t length);
    ByteBuffer& append(const std::string& str);
    ByteBuffer& append(const ByteBuffer& buffer);


    ByteBuffer& appendByte(u_int8_t byte);
    ByteBuffer& append2Bytes(u_int16_t word);
    ByteBuffer& append4Bytes(u_int32_t bytes);


    u_int8_t  getByte(size_t at);
    u_int16_t getWord(size_t at);
    u_int32_t get4Bytes(size_t at);


    u_int8_t  popByte();
    u_int16_t popWord();
    u_int32_t pop4Bytes();


    const u_int8_t * data() const;


    size_t size() const;


    std::string toString() const;


    ByteBuffer& operator+=(const ByteBuffer& buffer);
    ByteBuffer& operator=(const ByteBuffer& buffer);
};



// Operators

inline bool operator==(const ByteBuffer& one, const ByteBuffer& another)
{
    return (one.size() == another.size()) && (memcmp(one.data(), another.data(), one.size()) == 0);
}


inline bool operator!=(const ByteBuffer& one, const ByteBuffer& another)
{
    return (one.size() != another.size()) || (memcmp(one.data(), another.data(), one.size()) != 0);
}


inline ByteBuffer operator+(const ByteBuffer& one, const ByteBuffer& another)
{
    return ByteBuffer(one).append(another);
}


#endif
