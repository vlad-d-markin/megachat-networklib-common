#ifndef TCPSOCKETEXCEPTION_H
#define TCPSOCKETEXCEPTION_H

#include <exceptions/exception.h>

class TcpSocketException : public Exception {
public:
    TcpSocketException(std::string reason) : Exception(reason) {}
    TcpSocketException(std::string reason, int error_code) : Exception(reason, error_code) {}
};

#endif
