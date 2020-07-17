/*
 * ods_error.cpp
 * Andrew Mikalsen
 * 7/16/20
 */

#include <ods_error.h>

namespace One_data_share {
    Ods_error::Ods_error(const std::string& what_arg)
        : runtime_error(what_arg) {}

    Ods_error::Ods_error(const char* what_arg)
        : runtime_error(what_arg) {}

    Ods_error::~Ods_error() = default;

    IO_error::IO_error(const std::string& what_arg)
        : Ods_error(what_arg) {}

    IO_error::IO_error(const char* what_arg)
        : Ods_error(what_arg) {}

    IO_error::~IO_error() = default;

    Unexpected_response_error::Unexpected_response_error(const std::string& what_arg, int status)
        : Ods_error(what_arg), status(status) {}

    Unexpected_response_error::Unexpected_response_error(const char* what_arg, int status)
        : Ods_error(what_arg), status(status) {}
        
    Unexpected_response_error::~Unexpected_response_error() = default;
}