#ifndef IPADDRESSEXCEPTION_H
#define IPADDRESSEXCEPTION_H

#include "exception.h"



class IpAddressException : public Exception {
public:
    IpAddressException(std::string reason) : Exception(reason) {}
    IpAddressException(std::string reason, int error_code) : Exception(reason, error_code) {}
};



class InvalidAddressException : public IpAddressException {
public:
    InvalidAddressException(std::string reason) : IpAddressException(reason) {}
    InvalidAddressException(std::string reason, int error_code) : IpAddressException(reason, error_code) {}
};

class InvalidPortException : public IpAddressException {
public:
    InvalidPortException(std::string reason) : IpAddressException(reason) {}
    InvalidPortException(std::string reason, int error_code) : IpAddressException(reason, error_code) {}
};

#endif
