#include <bytebuffer.h>

#include <string.h>



ByteBuffer::ByteBuffer(const char *c_str)
{
    fromRawData(c_str, strlen(c_str));
}


ByteBuffer::ByteBuffer(std::string str)
{
    fromRawData(str.c_str(), str.length());
}



ByteBuffer::ByteBuffer(const char *raw_data, size_t len)
{
    fromRawData(raw_data, len);
}



void ByteBuffer::fromRawData(const char *raw_data, size_t len)
{
    m_data.insert(m_data.begin(), raw_data, raw_data + len);
    m_data.resize(len);
}



size_t ByteBuffer::size() const
{
    return m_data.size();
}



const char * ByteBuffer::rawData() const
{
    return &m_data[0];
}



void ByteBuffer::appendRaw(const char *raw_data, size_t len)
{
    const size_t old_size = size();
    m_data.resize(old_size + len);

    m_data.insert(m_data.end(), raw_data, raw_data + len);
}



void ByteBuffer::appendString(const std::string str)
{
    const size_t old_size = size();
    m_data.resize(old_size + str.length());

    m_data.insert(m_data.end(), str.c_str(), str.c_str() + str.length());
}



void ByteBuffer::append(ByteBuffer buffer)
{
    appendRaw(buffer.rawData(), buffer.size());
}



ByteBuffer ByteBuffer::extractFrom(int from)
{
    return ByteBuffer(rawData() + from, m_data.size() - from);
}



std::string ByteBuffer::toString()
{
    return std::string(rawData(), size());
}
