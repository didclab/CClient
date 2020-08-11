/**
 * @file error_message.h
 * Defines namespace-global constants for error messages.
 *
 * @author Andrew Mikalsen
 * @date 8/10/20
 */

#ifndef ONEDATASHARE_ERROR_MESSAGE_H
#define ONEDATASHARE_ERROR_MESSAGE_H

namespace One_data_share {
namespace Internal {
namespace Err {

/** Error message when a 303 response code is expected and not received. */
constexpr auto expect_303_msg {"Expected a status 303 response code"};

/** Error message when a Location header is expected and not received. */
constexpr auto expect_location_msg {"Expected a \"Location\" header in the response headers"};

/** Error message when a 200 status code is expected and not received. */
constexpr auto expect_200_msg {"Expected a 200 response code"};

/** Error message when using an undefined value of an enumeration. */
constexpr auto unknown_enum_msg {"Unknown enumeration type"};

/** Error message when unable to parse the expected JSON response. */
constexpr auto invalid_json_body_msg {"Unable to parse expected JSON response body"};

/** Error message when a parsed resource is a directory but defines no field for contained resources. */
constexpr auto expect_resources_msg {"Expected parsed directory to define contained resources"};

/** Error message when a parsed resource from an id-endpoint defines no field for id. */
constexpr auto expect_id_msg {"Expected parsed resource to define an id"};

} // namespace Err
} // namespace Internal
} // namespace One_data_share

#endif // ONEDATASHARE_ERROR_MESSAGE_H
