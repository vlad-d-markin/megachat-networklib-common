#include <bytebuffer.h>


#include <iostream>


ByteBuffer::ByteBuffer() {}


ByteBuffer::ByteBuffer(const ByteBuffer &buffer)
{
    set(buffer);
}



ByteBuffer::ByteBuffer(const u_int8_t *raw_data, size_t length)
{
    set(raw_data, length);
}



ByteBuffer::ByteBuffer(const std::string &str)
{
    set(str);
}



void ByteBuffer::clear()
{
    m_data.clear();
}



ByteBuffer ByteBuffer::cut(int from, int to)
{
    if(to > 0 && to < from) {
        throw ByteBufferException("When cutting from nust be less than to.");
    }

    size_t len = size() - from;

    if(to > 0) {
        len = to - from;
    }

    return ByteBuffer(&m_data[from], len);
}



ByteBuffer& ByteBuffer::removeFront(size_t bytes)
{
    if(bytes > size())
        throw ByteBufferException("Can't remove more than it is in buffer");

    m_data.erase(m_data.begin(), m_data.begin() + bytes);
    return *this;
}



ByteBuffer& ByteBuffer::removeRear(size_t bytes)
{
    if(bytes > size())
        throw ByteBufferException("Can't remove more than it is in buffer");

    m_data.erase(m_data.end() - bytes, m_data.end());

    return *this;
}



ByteBuffer& ByteBuffer::setAt(size_t pos, u_int16_t word)
{
    m_data.insert(m_data.begin() + pos, (u_int8_t *) &word, ((u_int8_t *) &word) + sizeof(word));

    return *this;
}



ByteBuffer& ByteBuffer::set(const u_int8_t *raw_data, size_t length)
{
    m_data.clear();
    return append(raw_data, length);
}



ByteBuffer& ByteBuffer::set(const std::string &str)
{
    m_data.clear();
    return append(str);
}



ByteBuffer& ByteBuffer::set(const ByteBuffer &buffer)
{
    m_data.clear();
    return append(buffer);
}



ByteBuffer& ByteBuffer::append(const u_int8_t *raw_data, size_t length)
{
    m_data.insert(m_data.end(), raw_data, raw_data + length);
    return * this;
}



ByteBuffer& ByteBuffer::append(const std::string &str)
{
    return append((uint8_t *)str.c_str(), str.length());
}



ByteBuffer& ByteBuffer::append(const ByteBuffer &buffer)
{
    return append(buffer.data(), buffer.size());
}



ByteBuffer& ByteBuffer::appendByte(u_int8_t byte)
{
    return append(&byte, sizeof(uint8_t));
}



ByteBuffer& ByteBuffer::append2Bytes(u_int16_t word)
{
    return append((uint8_t *) &word, sizeof(uint16_t));
}



ByteBuffer& ByteBuffer::append4Bytes(u_int32_t bytes)
{
    return append((uint8_t *) &bytes, sizeof(uint32_t));
}



const u_int8_t * ByteBuffer::data() const
{
    return &m_data[0];
}



size_t ByteBuffer::size() const
{
    return m_data.size();
}



std::string ByteBuffer::toString() const
{
    return std::string((char *)data(), size());
}



u_int8_t ByteBuffer::getByte(size_t at)
{
    if(at < 0 || at >= size())
        throw ByteBufferException("Out of buffer");
    return m_data[at];
}



u_int16_t ByteBuffer::getWord(size_t at)
{
    if(at < 0 || at >= size())
        throw ByteBufferException("Out of buffer");

    u_int16_t d;
    memcpy(&d, &m_data[at], sizeof(d));
    return d;
}



u_int32_t ByteBuffer::get4Bytes(size_t at)
{
    if(at < 0 || at >= size())
        throw ByteBufferException("Out of buffer");

    u_int32_t d;
    memcpy(&d, &m_data[at], sizeof(d));
    return d;
}




u_int8_t ByteBuffer::popByte()
{
    if(size() == 0)
        throw ByteBufferException("Nothing to pop");

    u_int8_t b = getByte(0);
    m_data.erase(m_data.begin(), m_data.begin() + sizeof(b));

    return b;
}



u_int16_t ByteBuffer::popWord()
{
    if(size() == 0)
        throw ByteBufferException("Nothing to pop");

    u_int16_t b = getWord(0);
    m_data.erase(m_data.begin(), m_data.begin() + sizeof(b));

    return b;
}



u_int32_t ByteBuffer::pop4Bytes()
{
    if(size() == 0)
        throw ByteBufferException("Nothing to pop");

    u_int32_t b = get4Bytes(0);
    m_data.erase(m_data.begin(), m_data.begin() + sizeof(b));

    return b;
}



////////////////////////////////////////////////////
// Operators
////////////////////////////////////////////////////

ByteBuffer& ByteBuffer::operator+=(const ByteBuffer & buffer)
{
    append(buffer);
    return * this;
}


ByteBuffer& ByteBuffer::operator=(const ByteBuffer & buffer)
{
    set(buffer);
    return * this;
}
