/*
 * ODSException.cpp
 * Andrew Mikalsen
 * 7/15/20
 */

#include <ODSException.hpp>

namespace ods {
    ODSException::ODSException(const std::string& what_arg) : std::runtime_error(what_arg) {
    }
    ODSException::ODSException(const char* what_arg) : std::runtime_error(what_arg) {
    }
    ODSException::~ODSException() = default;

    ODSConnectionException::ODSConnectionException(const std::string& what_arg) : ODSException(what_arg) {
    }
    ODSConnectionException::ODSConnectionException(const char* what_arg) : ODSException(what_arg) {
    }
    ODSConnectionException::~ODSConnectionException() = default;

    ODSInternalServerException::ODSInternalServerException(const std::string& what_arg) : ODSException(what_arg) {
    }
    ODSInternalServerException::ODSInternalServerException(const char* what_arg) : ODSException(what_arg) {
    }
    ODSInternalServerException::~ODSInternalServerException() = default;

    ODSUnexpectedResponseException::ODSUnexpectedResponseException(const std::string& what_arg, const std::string& body, int status) : 
        ODSException(what_arg),
        _body(body),
        _status(status) {
    }
    
    ODSUnexpectedResponseException::ODSUnexpectedResponseException(const char* what_arg, const std::string& body, int status) :
        ODSException(what_arg),
        _body(body),
        _status(status) {
    }

    const std::string& ODSUnexpectedResponseException::body() const {
        return _body;
    }

    int ODSUnexpectedResponseException::status() const {
        return _status;
    }

    ODSUnexpectedResponseException::~ODSUnexpectedResponseException() = default;
}