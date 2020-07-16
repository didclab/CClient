/*
 * IOException.cpp
 * Andrew Mikalsen
 */

#include <IOException.hpp>

namespace ods {
    IOException::IOException(const std::string& what_arg) : OneDataShareException(what_arg) {
    }
    IOException::IOException(const char* what_arg) : OneDataShareException(what_arg) {
    }
    IOException::~IOException() = default;
}