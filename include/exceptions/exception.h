#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <string>
#include <errno.h>
#include <string.h>


/**
 * @brief Base exception class for all exceptions in this library
 * <p>
 * Container for a string, also can describe given errno.
 */
class Exception {
protected:
    std::string m_description;      ///< Exception description
    int         m_error_code;       ///< Last errno

public:
    explicit Exception(std::string reason) : m_description(reason), m_error_code(0) {}
    explicit Exception(std::string reason, int error_code)
    {
        m_description = reason;
        m_error_code = error_code;

        if(error_code != 0)
        {
            char error_description_buff[512];
            char * descr = ::strerror_r(error_code, error_description_buff, 512);

            m_description += " (" + std::string(descr) + ")";
        }

    }

    virtual const std::string& description() const { return m_description; }
};

#endif
