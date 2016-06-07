#include <bytebuffer.h>


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



ByteBuffer ByteBuffer::cut(size_t from, size_t to)
{
    if(to < from) {
        //throw
    }

    ByteBuffer new_bb;
    new_bb.set(* this);

    if(to > 0)
        new_bb.removeRear(new_bb.size() - to);

    if(from > 0) {
        new_bb.removeFront(from);
    }

    return new_bb;
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




////////////////////////////////////////////////////
// Operators
////////////////////////////////////////////////////

ByteBuffer& ByteBuffer::operator+=(ByteBuffer & buffer)
{
    append(buffer);
    return * this;
}

