/*
 * CredentialServiceImpl.cpp
 * Andrew Mikalsen
 * 7/10/20
 */

#include <stdexcept>
#include <iomanip>
#include <sstream>
#include <utility>
#include "CredentialServiceImpl.hpp"
#include <ODSException.hpp>

namespace ods {
    namespace internal {

        namespace {
            /**
             * Path of the REST API call for oauth.
            */
            constexpr auto API_PATH_OAUTH = "/api/oauth";

            /**
             * Path of the REST API call for credentials.
             */
            constexpr auto API_PATH_CRED = "/api/cred";

            constexpr auto HEADER_CONTENT_TYPE = "Content-Type";
            constexpr auto HEADER_JSON = "application/json";
            constexpr auto HEADER_AUTHORIZATION = "Authorization";
            constexpr auto HEADER_BEARER = "Bearer ";
            constexpr auto HEADER_LOCATION = "Location";

            /**
             * Creates the required header map using the specified token.
             * 
             * @param ods_auth_token token used to create the headers
             * 
             * @return map of the headers needed to make REST API calls
             */
            std::unordered_multimap<std::string, std::string> create_headers(const std::string& ods_auth_token) {
                std::unordered_multimap<std::string, std::string> headers;
                headers.insert(std::pair<std::string, std::string>(HEADER_CONTENT_TYPE, HEADER_JSON));
                headers.insert(std::pair<std::string, std::string>(HEADER_AUTHORIZATION, HEADER_BEARER + ods_auth_token));

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
            std::string endpoint_as_string(const CredentialEndpointType type) {
                switch (type) {
                    case CredentialEndpointType::FTP:
                        return "ftp";
                    case CredentialEndpointType::HTTP:
                        return "http";
                    case CredentialEndpointType::S3:
                        return "s3";
                    case CredentialEndpointType::SFTP:
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
            std::string endpoint_as_string(const OAuthEndpointType type) {
                switch (type) {
                    case OAuthEndpointType::BOX:
                        return "box";
                    case OAuthEndpointType::DROPBOX:
                        return "dropbox";
                    case OAuthEndpointType::GFTP:
                        return "gftp";
                    case OAuthEndpointType::GOOGLE_DRIVE:
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
            std::string endpoint_as_string(const EndpointType type) {
                switch (type) {
                    case EndpointType::BOX:
                        return "box";
                    case EndpointType::DROPBOX:
                        return "dropbox";
                    case EndpointType::FTP:
                        return "ftp";
                    case EndpointType::GFTP:
                        return "gftp";
                    case EndpointType::GOOGLE_DRIVE:
                        return "gdrive";
                    case EndpointType::HTTP:
                        return "http";
                    case EndpointType::S3:
                        return "s3";
                    case EndpointType::SFTP:
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

        CredentialServiceImpl::CredentialServiceImpl(const std::string& ods_auth_token, const std::string& ods_url, std::unique_ptr<rest::Rest> rest_caller) :
            _ods_auth_token(ods_auth_token),
            _ods_url(ods_url),
            _rest_caller(std::move(rest_caller)),
            _headers(create_headers(_ods_auth_token)) {
        }

        std::string CredentialServiceImpl::oauth_url(const OAuthEndpointType type) const {
            try {
                const rest::Response response(_rest_caller->get(_ods_url+API_PATH_OAUTH+"?type="+endpoint_as_string(type), _headers));
                if (response.status() != 303) {
                    // may be invalid token
                    throw ODSUnexpectedResponseException("Expected a status 303 response code when requesting oauth url.", response.body(), response.status());
                }
                // find url in a single location header, as there should only be one
                const std::unordered_multimap<std::string, std::string>::const_iterator iter(response.headers().find(HEADER_LOCATION));
                if (iter == response.headers().end()) {
                    // did not contain location header
                    throw ODSUnexpectedResponseException("Expected a \""+std::string(HEADER_LOCATION)+"\" header in the response.", response.body(), response.status());
                }
                return iter->second;
            } catch (ODSUnexpectedResponseException e) {
                throw e;
            } catch (std::runtime_error e) {
                throw ODSConnectionException(std::string(e.what()));
            }
        }

        bool CredentialServiceImpl::register_credential(const CredentialEndpointType type, const std::string& cred_id, const std::string& uri, const std::string& username, const std::string& secret) const {
            try {
                const rest::Response response(_rest_caller->post(_ods_url+API_PATH_CRED+"/"+endpoint_as_string(type), _headers, create_account_endpoint_credential(cred_id, uri, username, secret)));
                if (response.status() == 200) {
                    return true;
                } else if (response.status() == 500) {
                    throw ODSUnexpectedResponseException("Internal server error when registering credential.", response.body(), response.status());
                }
                return false;
            } catch (ODSUnexpectedResponseException e) {
                throw e;
            } catch (std::runtime_error e) {
                throw ODSConnectionException(std::string(e.what()));
            }
        }

        std::vector<std::string> CredentialServiceImpl::credential_id_list(const EndpointType type) const {
            // TODO: implement
            return std::vector<std::string>();
        }


        CredentialServiceImpl::~CredentialServiceImpl() = default;
    }
}