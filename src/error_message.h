/*
 * error_message.h
 * Andrew Mikalsen
 * 8/10/20
 */

#ifndef ONEDATASHARE_ERROR_MESSAGE_H
#define ONEDATASHARE_ERROR_MESSAGE_H

namespace One_data_share {
namespace Internal {

/** Error message when a 303 response code is expected and not received. */
constexpr char* expect_303_msg;

/** Error message when a Location header is expected and not received. */
constexpr char* expect_location_msg;

/** Error message when a 200 status code is expected and not received. */
constexpr char* expect_200_msg;

/** Error message when using an undefined value of an enumeration. */
constexpr char* unknown_enum_msg;

/** Error message when unable to parse the expected JSON response. */
constexpr char* invalid_json_body_msg;

} // namespace Internal
} // namespace One_data_share

#endif // ONEDATASHARE_ERROR_MESSAGE_H