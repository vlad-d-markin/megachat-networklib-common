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


    ByteBuffer& set(const u_int8_t * raw_data, size_t length);
    ByteBuffer& set(const std::string& str);
    ByteBuffer& set(const ByteBuffer& buffer);


    ByteBuffer& append(const u_int8_t * raw_data, size_t length);
    ByteBuffer& append(const std::string& str);
    ByteBuffer& append(const ByteBuffer& buffer);


    const u_int8_t * data() const;


    size_t size() const;


    std::string toString() const;


    ByteBuffer& operator+=(ByteBuffer& buffer);
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
