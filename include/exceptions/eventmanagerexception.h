#ifndef EVENTMANAGEREXCEPTION_H
#define EVENTMANAGEREXCEPTION_H

#include <string>

#include "exception.h"


class EventManagerException : public Exception {
public:
    EventManagerException(std::string reason) : Exception(reason) {}
    EventManagerException(std::string reason, int error_code) : Exception(reason, error_code) {}
};

#endif
