/*
 * OneDataShareException.cpp
 * Andrew Mikalsen
 * 7/16/20
 */

#include <OneDataShareException.hpp>

namespace ods {
    OneDataShareException::OneDataShareException(const std::string& what_arg) : runtime_error(what_arg) {
    }
    OneDataShareException::OneDataShareException(const char* what_arg) : runtime_error(what_arg) {
    }
    OneDataShareException::~OneDataShareException() = default;
}