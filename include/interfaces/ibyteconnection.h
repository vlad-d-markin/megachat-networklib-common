#ifndef IBYTECONNECTION_H
#define IBYTECONNECTION_H

#include <string>
#include <bytebuffer.h>

class IByteConnection {
public:
    virtual void open() = 0;


    virtual void close() = 0;


    virtual void send(ByteBuffer data) = 0;
};

#endif
