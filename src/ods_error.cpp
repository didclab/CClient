/**
 * @file ods_error.cpp
 *
 * @author Andrew Mikalsen
 * @date 7/16/20
 */

#include <onedatashare/ods_error.h>

namespace Onedatashare {

Unexpected_response_error::Unexpected_response_error(const std::string& what_arg, int status)
    : Ods_error {what_arg},
      status {status}
{}

} // namespace Onedatashare
