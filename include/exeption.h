#ifndef EXEPTION_H
#define EXEPTION_H

#include "./interface/ithrowable.h"

#include <string>

class Exeption : public IThrowable {
private:
    std::string m_reason;

public:
    Exeption(std::string reason = "Some reason");
    virtual ~Exeption();

    virtual std::string what() const;

};


#endif /* EXEPTION_H */

