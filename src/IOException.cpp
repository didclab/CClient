/*
 * IOException.cpp
 * Andrew Mikalsen
 */

#include <IOException.hpp>

namespace ods {
    IOException::IOException(const std::string& what_arg) : runtime_error(what_arg) {
    }
    IOException::IOException(const char* what_arg) : runtime_error(what_arg) {
    }
    IOException::~IOException() = default;
}