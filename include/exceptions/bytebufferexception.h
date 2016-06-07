#ifndef BYTEBUFFEREXCEPTION_H
#define BYTEBUFFEREXCEPTION_H

#include "exception.h"

class ByteBufferException : public Exception {
public:
    ByteBufferException(std::string reason) : Exception(reason) {}
};

#endif
