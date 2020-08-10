/*
 * credential_service_impl.cpp
 * Andrew Mikalsen
 * 7/10/20
 */

#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <utility>

#include <simdjson/simdjson.h>

#include <onedatashare/ods_error.h>

#include "credential_service_impl.h"
#include "utils.h"

namespace One_data_share {

namespace Internal {

namespace {

/** Path of the REST API call for oauth. */
constexpr auto api_path_oauth {"/api/oauth"};

/** Path of the REST API call for credentials. */
constexpr auto api_path_cred {"/api/cred"};

/** Error message when a status code other than 303 is received when requesting an oauth url. */
constexpr auto oauth_no_303_msg {"Expected a status 303 response code when requesting oauth url."};

/** Error message when there is no location in the response headers when requesting an oauth url. */
constexpr auto oauth_no_location_msg {
    "Response headers missing the expected \"Location\" header when reqesting oauth url."};

/** Error message when a status code other than 200 is received when registering credentials. */
constexpr auto reg_cred_no_200_msg {"Expected a 200 response code when registering credentials."};

/** Error message when converting an invalid Credential_endpoint_type to a string. */
constexpr auto bad_cred_endpoint_msg {"Unknown Credential_endpoint_type."};

/** Error message when converting an invalid Oauth_endpoint_type to a string. */
constexpr auto bad_oauth_endpoint_msg {"Unknown Oauth_endpoint_type."};

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
        return "ftp";
    case Credential_endpoint_type::http:
        return "http";
    case Credential_endpoint_type::s3:
        return "s3";
    case Credential_endpoint_type::sftp:
        return "sftp";
    default:
        // invalid enum
        throw std::invalid_argument(bad_cred_endpoint_msg);
    }
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
        return "box";
    case Oauth_endpoint_type::dropbox:
        return "dropbox";
    case Oauth_endpoint_type::gftp:
        return "gftp";
    case Oauth_endpoint_type::google_drive:
        return "gdrive";
    default:
        // invalid enum
        throw std::invalid_argument(bad_oauth_endpoint_msg);
    }
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
           << "\"accountId\":\"" << escape_json(account_id) << "\",\"uri\":\"" << escape_json(uri);
    if (username != nullptr) {
        stream << "\",\"username\":\"" << escape_json(*username);
    }
    if (secret != nullptr) {
        stream << "\",\"secret\":\"" << escape_json(*secret);
    }
    stream << "\"}";

    return stream.str();
}

} // namespace

Credential_service_impl::Credential_service_impl(const std::string& ods_auth_token,
                                                 const std::string& ods_url,
                                                 std::unique_ptr<Rest> rest_caller)
    : ods_auth_token_ {ods_auth_token},
      ods_url_ {ods_url},
      rest_caller_ {std::move(rest_caller)},
      headers_ {create_headers(ods_auth_token_)}
{}

std::string Credential_service_impl::oauth_url(const Oauth_endpoint_type type) const
{
    // if get throws an exception, propagate it up
    const Response response {rest_caller_->get(ods_url_ + api_path_oauth + "?type=" + as_string(type), headers_)};

    if (response.status != 303) {
        // unexpected response
        throw Unexpected_response_error {oauth_no_303_msg, response.status};
    }

    // find url in a single location header, as there should only be one
    const auto iter {response.headers.find("Location")};
    if (iter == response.headers.end()) {
        // did not contain Location header
        throw Unexpected_response_error {oauth_no_location_msg, response.status};
    }

    return iter->second;
}

void Credential_service_impl::register_credential(const Credential_endpoint_type type,
                                                  const std::string& cred_id,
                                                  const std::string& uri,
                                                  const std::string* username,
                                                  const std::string* secret) const
{
    // if post throws an exception, propogate it up
    const Response response {rest_caller_->post(ods_url_ + api_path_cred + "/" + as_string(type),
                                                headers_,
                                                create_account_endpoint_credential(cred_id, uri, username, secret))};

    if (response.status != 200) {
        // expected status 200
        throw Unexpected_response_error {reg_cred_no_200_msg, response.status};
    }
}

std::vector<std::string> Credential_service_impl::credential_id_list(const Endpoint_type type) const
{
    // if get throws an exception, propogate it up
    const auto response {rest_caller_->get(ods_url_ + api_path_cred + "/" + as_string(type), headers_)};

    if (response.status != 200) {
        // expected status 200
        throw Unexpected_response_error {"Expected a status 200 response when fetching the credential id list.",
                                         response.status};
    }

    // parse string array in CredList from response body
    simdjson::dom::parser parser {};
    std::vector<std::string> cred_list {};
    try {
        for (auto e : parser.parse(response.body).get_object().value()["credentialList"].get_array()) {
            cred_list.push_back(e.get_c_str().take_value());
        }
    } catch (simdjson::simdjson_error e) {
        // bad response body
        throw Unexpected_response_error {
            std::string("Failed to parse response body when fetching the credential id list: ") + e.what(),
            response.status};
    }

    return cred_list;
}

} // namespace Internal

} // namespace One_data_share