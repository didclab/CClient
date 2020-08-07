/*
 * ods_error.cpp
 * Andrew Mikalsen
 * 7/16/20
 */

#include <onedatashare/ods_error.h>

namespace One_data_share {

Unexpected_response_error::Unexpected_response_error(const std::string& what_arg, int status)
    : Ods_error {what_arg},
      status {status}
{}

} // namespace One_data_share