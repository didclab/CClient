/*
 * error_message.cpp
 * Andrew Mikalsen
 * 8/10/20
 */

#include "error_message.h"

namespace One_data_share {
namespace Internal {

/** Error message when a 303 response code is expected and not received. */
constexpr char* expect_303_msg {"Expected a status 303 response code."};

/** Error message when a Location header is expected and not received. */
constexpr char* expect_location_msg {"Expected a \"Location\" header in the response headers."};

/** Error message when a 200 status code is expected and not received. */
constexpr char* expect_200_msg {"Expected a 200 response code when registering credentials."};

/** Error message when using an undefined value of an enumeration. */
constexpr char* unknown_enum_msg {"Unknown enumeration type."};

/** Error message when unable to parse the expected JSON response. */
constexpr char* invalid_json_body_msg {"Unable to parse expected JSON response body."};

} // namespace Internal
} // namespace One_data_share