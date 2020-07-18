/*
 * credential_service_impl.cpp
 * Andrew Mikalsen
 * 7/10/20
 */

#include <iomanip>
#include <sstream>
#include <utility>
#include <onedatashare/ods_error.h>
#include "credential_service_impl.h"

namespace {

    using namespace One_data_share;

    /**
     * Path of the REST API call for oauth.
    */
    constexpr auto api_path_oauth = "/api/oauth";

    /**
     * Path of the REST API call for credentials.
     */
    constexpr auto api_path_cred = "/api/cred";

    constexpr auto header_content_type = "Content-Type";
    constexpr auto header_json = "application/json";
    constexpr auto header_authorization = "Authorization";
    constexpr auto header_bearer = "Bearer ";

    constexpr auto oauth_url_wrong_response_msg = "Expected a status 303 response code when requesting oauth url.";

    constexpr auto oauth_url_missing_location_msg = "Response headers missing the expected \"Location\" header when reqesting oauth url.";

    constexpr auto register_cred_wrong_response_msg = "Expected a 200 response code when registering credentials.";

    /**
     * Creates the required header map using the specified token.
     * 
     * @param ods_auth_token token used to create the headers
     * 
     * @return map of the headers needed to make REST API calls
     */
    std::unordered_multimap<std::string, std::string> create_headers(const std::string& ods_auth_token) {
        std::unordered_multimap<std::string, std::string> headers;
        headers.insert(std::pair<std::string, std::string>(header_content_type, header_json));
        headers.insert(std::pair<std::string, std::string>(header_authorization, header_bearer + ods_auth_token));

        return headers;
    }

    /**
     * Converts a credential endpoint type to the string needed for the
     * REST API.
     * 
     * @param type endpoint type to convert
     * 
     * @return endpoint type as a string understood by the REST API
     */
    std::string endpoint_as_string(const Credential_endpoint_type type) {
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
                // TODO: throw exception
                return "";
        }
    }

    /**
     * Converts an OAuth endpoint type to the string needed for the REST
     * API.
     * 
     * @param type endpoint type to convert
     * 
     * @return endpoint type as a string understood by the REST API
     */
    std::string endpoint_as_string(const Oauth_endpoint_type type) {
        switch (type) {
            case Oauth_endpoint_type::box:
                return "box";
            case Oauth_endpoint_type::dropbox:
                return "dropbox";
            case Oauth_endpoint_type::gftp:
                return "gftp";
            case Oauth_endpoint_type::googledrive:
                return "gdrive";
            default:
                // TODO: throw exception
                return "";
        }
    }

    /**
     * Converts an endpoint type to the string needed for the REST
     * API.
     * 
     * @param type endpoint type to convert
     * 
     * @return endpoint type as a string understood by the REST API
     */
    std::string endpoint_as_string(const Endpoint_type type) {
        switch (type) {
            case Endpoint_type::box:
                return "box";
            case Endpoint_type::dropbox:
                return "dropbox";
            case Endpoint_type::ftp:
                return "ftp";
            case Endpoint_type::gftp:
                return "gftp";
            case Endpoint_type::google_drive:
                return "gdrive";
            case Endpoint_type::http:
                return "http";
            case Endpoint_type::s3:
                return "s3";
            case Endpoint_type::sftp:
                return "sftp";
            default:
                // TODO: throw exception
                return "";
        }
    }

    /**
     * Escapes characters in the given json string.
     * 
     * @param json borrowed reference to the json string to escape
     * 
     * @return a copy of the json string with its characters escaped
     */
    std::string escape_json(const std::string& json) {
        // see also: https://stackoverflow.com/questions/7724448/simple-json-string-escape-for-c/33799784#33799784
        std::ostringstream stream;
        for (auto c : json) {
            switch (c) {
                case '"':
                    stream << "\\\"";
                    break;
                case '\\':
                    stream << "\\\\";
                    break;
                case '\b':
                    stream << "\\b";
                    break;
                case '\f':
                    stream << "\\f";
                    break;
                case '\n':
                    stream << "\\n";
                    break;
                case '\r':
                    stream << "\\r";
                    break;
                case '\t':
                    stream << "\\t";
                    break;
                default:
                    if ('\x00' <= c && c <= '\x1f') {
                        stream << "\\u" << std::setfill('0') << (int) c;
                    } else {
                        stream << c;
                    }
            }
        }
        return stream.str();
    }

    std::string create_account_endpoint_credential(const std::string account_id, const std::string& uri, const std::string& username, const std::string& secret) {
        std::ostringstream stream;
        stream << "{" << "\"accountId\":\"" << escape_json(account_id) << "\",\"uri\":\"" << escape_json(uri) << "\",\"username\":\"" << escape_json(username) << "\",\"secret\":\"" << escape_json(secret) << "\"}";
        return stream.str();
    }
}

namespace One_data_share {
    Credential_service_impl::Credential_service_impl(const std::string& ods_auth_token, const std::string& ods_url, std::unique_ptr<Rest> rest_caller)
        : ods_auth_token_(ods_auth_token),
            ods_url_(ods_url),
            rest_caller_(std::move(rest_caller)),
            headers_(create_headers(ods_auth_token_)) {}

    std::string Credential_service_impl::oauth_url(const Oauth_endpoint_type type) const {
        // if get throws an exception, propagate it up
        const Response response(rest_caller_->get(ods_url_+api_path_oauth+"?type="+endpoint_as_string(type), headers_));

        if (response.status() != 303) {
            // unexpected response
            throw Unexpected_response_error(oauth_url_wrong_response_msg, response.status());
        }

        // find url in a single location header, as there should only be one
        const auto iter(response.headers().find("Location"));
        if (iter == response.headers().end()) {
            // did not contain Location header
            throw Unexpected_response_error(oauth_url_missing_location_msg, response.status());
        }

        return iter->second;
    }

    void Credential_service_impl::register_credential(const Credential_endpoint_type type, const std::string& cred_id, const std::string& uri, const std::string& username, const std::string& secret) const {
        // if post throws an exception, propogate it up
        const Response response(rest_caller_->post(ods_url_+api_path_cred+"/"+endpoint_as_string(type), headers_, create_account_endpoint_credential(cred_id, uri, username, secret)));
        
        if (response.status() != 200) {
            // expected status 200
            throw Unexpected_response_error(register_cred_wrong_response_msg, response.status());
        }
    }

    std::vector<std::string> Credential_service_impl::credential_id_list(const Endpoint_type type) const {
        // TODO: implement
        return std::vector<std::string>();
    }


    Credential_service_impl::~Credential_service_impl() = default;
}