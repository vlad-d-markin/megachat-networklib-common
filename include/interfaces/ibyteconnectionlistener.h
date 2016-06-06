#ifndef IBYTECONNECTIONLISTENER_H
#define IBYTECONNECTIONLISTENER_H

#include <string>



class IByteConnectionListener {
public:
    virtual void onOpened() = 0;


    virtual void onClosed() = 0;


    virtual void onReceived(std::string data) = 0;
};

#endif
