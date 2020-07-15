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
}