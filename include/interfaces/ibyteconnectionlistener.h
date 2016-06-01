#ifndef IBYTECONNECTIONLISTENER_H
#define IBYTECONNECTIONLISTENER_H

#include <string>
#include <bytebuffer.h>

class IByteConnectionListener {
public:
    virtual void onOpened() = 0;


    virtual void onClosed() = 0;


    virtual void onReceived(ByteBuffer data) = 0;
};

#endif
