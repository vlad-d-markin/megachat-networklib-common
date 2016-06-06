#ifndef IBYTECONNECTION_H
#define IBYTECONNECTION_H

#include <string>



class IByteConnection {
public:
    virtual void open() = 0;


    virtual void close() = 0;


    virtual void send(std::string data) = 0;
};

#endif
