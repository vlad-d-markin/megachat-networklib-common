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
//    m_data.resize(len);
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

    m_data.insert(m_data.end() - 1, raw_data, raw_data + len);

    m_data.resize(old_size + len);
}



void ByteBuffer::appendString(const std::string str)
{
    appendRaw(str.c_str(), str.length());

//    const size_t old_size = size();

//    m_data.insert(m_data.end()-1, str.begin(), str.end());
//    m_data.resize(old_size + str.length() - 1);
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
