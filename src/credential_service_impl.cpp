/**
 * @file credential_service_impl.cpp
 *
 * @author Andrew Mikalsen
 * @date 7/10/20
 */

#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <utility>

#include <simdjson/simdjson.h>

#include <onedatashare/ods_error.h>

#include "credential_service_impl.h"
#include "error_message.h"
#include "ods_rest_api.h"
#include "util.h"

namespace One_data_share {
namespace Internal {

namespace {
/**
 * Converts a credential endpoint type to the string needed for the REST API.
 *
 * @param type endpoint type to convert
 *
 * @return endpoint type as a string understood by the REST API
 */
std::string as_string(Credential_endpoint_type type)
{
    switch (type) {
    case Credential_endpoint_type::ftp:
        return Api::ftp_type;
    case Credential_endpoint_type::http:
        return Api::http_type;
    case Credential_endpoint_type::s3:
        return Api::s3_type;
    case Credential_endpoint_type::sftp:
        return Api::sftp_type;
    }

    throw std::invalid_argument(Err::unknown_enum_msg);
}

/**
 * Converts an OAuth endpoint type to the string needed for the REST API.
 *
 * @param type endpoint type to convert
 *
 * @return endpoint type as a string understood by the REST API
 */
std::string as_string(Oauth_endpoint_type type)
{
    switch (type) {
    case Oauth_endpoint_type::box:
        return Api::box_type;
    case Oauth_endpoint_type::dropbox:
        return Api::dropbox_type;
    case Oauth_endpoint_type::gftp:
        return Api::gftp_type;
    case Oauth_endpoint_type::google_drive:
        return Api::google_drive_type;
    }

    throw std::invalid_argument(Err::unknown_enum_msg);
}

/**
 * Creates an AccountEndpointCredential json object with the specified fields.
 *
 * @param account_id borrowed reference to the value of the corresponding json field
 * @param uri borrowed reference to the value of the corresponding json field
 * @param account_id borrowed pointer to the value of the corresponding json field or nullptr to exclude the json field
 * @param secret borrowed pointer to the value of the corresponding json field or nullptr to exclude the json field
 *
 * @return the created json string corresponding to the AccountEndpointCredential json object
 */
std::string create_account_endpoint_credential(const std::string& account_id,
                                               const std::string& uri,
                                               const std::string* username,
                                               const std::string* secret)
{
    std::ostringstream stream {};
    stream << "{"
           << "\"accountId\":\"" << Util::escape_json(account_id) << "\",\"uri\":\"" << Util::escape_json(uri);
    if (username != nullptr) {
        stream << "\",\"username\":\"" << Util::escape_json(*username);
    }
    if (secret != nullptr) {
        stream << "\",\"secret\":\"" << Util::escape_json(*secret);
    }
    stream << "\"}";

    return stream.str();
}

} // namespace

Credential_service_impl::Credential_service_impl(const std::string& ods_auth_token,
                                                 const std::string& ods_url,
                                                 std::unique_ptr<Rest> rest_caller)
    : ods_url_ {ods_url},
      headers_ {Util::create_headers(ods_auth_token)},
      rest_caller_ {std::move(rest_caller)}
{}

std::string Credential_service_impl::oauth_url(Oauth_endpoint_type type) const
{
    // if get throws an exception, propagate it up
    const Response response {rest_caller_->get(ods_url_ + Api::oauth_path + "?type=" + as_string(type), headers_)};

    if (response.status != 303) {
        throw Unexpected_response_error {Err::expect_303_msg, response.status};
    }

    // find url contained in a Location header (there should only be one Location header)
    const auto iter {response.headers.find("Location")};

    // check that there was a Location header
    if (iter == response.headers.end()) {
        throw Unexpected_response_error {Err::expect_location_msg, response.status};
    }

    // return the url
    return iter->second;
}

void Credential_service_impl::register_credential(Credential_endpoint_type type,
                                                  const std::string& cred_id,
                                                  const std::string& uri,
                                                  const std::string* username,
                                                  const std::string* secret) const
{
    // if post throws an exception, propogate it up
    const Response response {rest_caller_->post(ods_url_ + Api::cred_path + "/" + as_string(type),
                                                headers_,
                                                create_account_endpoint_credential(cred_id, uri, username, secret))};

    if (response.status != 200) {
        throw Unexpected_response_error {Err::expect_200_msg, response.status};
    }
}

std::vector<std::string> Credential_service_impl::credential_id_list(const Endpoint_type type) const
{
    // if get throws an exception, propogate it up
    const auto response {rest_caller_->get(ods_url_ + Api::cred_path + "/" + Util::as_string(type), headers_)};

    if (response.status != 200) {
        throw Unexpected_response_error {Err::expect_200_msg, response.status};
    }

    simdjson::dom::parser parser {};
    std::vector<std::string> cred_list {};

    try {
        // parse json string array in CredList json object from response body
        for (auto e : parser.parse(response.body).get_object().value()["credentialList"].get_array()) {
            cred_list.push_back(e.get_c_str().take_value());
        }
    } catch (simdjson::simdjson_error e) {
        // bad response body
        throw Unexpected_response_error {Err::invalid_json_body_msg, response.status};
    }

    return cred_list;
}

} // namespace Internal
} // namespace One_data_share
