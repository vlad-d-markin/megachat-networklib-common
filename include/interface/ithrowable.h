#ifndef ITHROWABLE_H
#define ITHROWABLE_H

#include <string>

class IThrowable {
public:
    virtual std::string what() const = 0;
};

#endif /* ITHROWABLE_H */

