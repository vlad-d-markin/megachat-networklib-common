#ifndef BYTEBUFFER_H
#define BYTEBUFFER_H

#include <vector>
#include <string>


class ByteBuffer {
private:
    std::vector<char> m_data;

public:
    ByteBuffer(std::string str = "");
    ByteBuffer(const char * c_str);
    ByteBuffer(const char * raw_data, size_t len);

    void appendString(const std::string str);
    void appendRaw(const char * raw_data, size_t len);
    void append(ByteBuffer buffer);

    ByteBuffer extractFrom(int from);

    const char * rawData() const;
    size_t size() const;

    std::string toString();

private:
    void fromRawData(const char * raw_data, size_t len);
};

#endif
