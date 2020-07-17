/*
 * UnexpectedResponseException.cpp
 * Andrew Mikalsen
 * 7/16/20
 */

#include <UnexpectedResponseException.hpp>

namespace ods {
    UnexpectedResponseException::UnexpectedResponseException(const std::string& what_arg, int status) : 
        runtime_error(what_arg),
        _status(status) {
    }

    UnexpectedResponseException::UnexpectedResponseException(const char* what_arg, int status) : 
        runtime_error(what_arg),
        _status(status) {

    }

    int UnexpectedResponseException::status() const {
        return _status;
    }
    
    UnexpectedResponseException::~UnexpectedResponseException() = default;
}