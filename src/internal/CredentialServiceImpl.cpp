/*
 * CredentialServiceImpl.cpp
 * Andrew Mikalsen
 * 7/10/20
 */

#include "CredentialServiceImpl.hpp"

#include <utility>

namespace ods {
    namespace internal {

        namespace {

            /**
             * Path of the REST API call for oauth.
            */
            const std::string API_PATH_OAUTH("/api/oauth");

            /**
             * Path of the REST API call for credentials.
             */
            const std::string API_PATH_CRED("/api/cred");

            const std::string HEADER_CONTENT_TYPE("Content-Type");
            const std::string HEADER_JSON("application/json");
            const std::string HEADER_AUTHORIZATION("Authorization");
            const std::string HEADER_BEARER("Bearer ");
            const std::string HEADER_LOCATION("Location");

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
             * Converts an OAuth endpoint type to the string needed for the REST
             * API.
             * 
             * @param type endpoint type to convert
             * 
             * @return endpoint type as a string understood by the REST API
             */
            std::string endpoint_to_string(OAuthEndpointType type) {
                switch (type) {
                    default:
                        // TODO: throw exception
                        return "";
                    case OAuthEndpointType::BOX:
                        return "box";
                    case OAuthEndpointType::DROPBOX:
                        return "dropbox";
                    case OAuthEndpointType::GFTP:
                        return "gftp";
                    case OAuthEndpointType::GOOGLE_DRIVE:
                        return "gdrive";
                }
            }

            std::string create_account_endpoint_credential() {
                // TODO: implement
                return "";
            }
        }

        CredentialServiceImpl::CredentialServiceImpl(const std::string& ods_auth_token, const std::string& ods_url, std::unique_ptr<rest::Rest> rest_caller) :
            _ods_auth_token(ods_auth_token),
            _ods_url(ods_url),
            _rest_caller(std::move(rest_caller)),
            _headers(create_headers(_ods_auth_token)) {
        }

        std::string CredentialServiceImpl::oauth_url(OAuthEndpointType type) const {
            const rest::Response response(_rest_caller->get(_ods_url+API_PATH_OAUTH+"?type="+endpoint_to_string(type), _headers));
            if (response.status() != 303) {
                // TODO: handle error (expected status code 303)
                return "error: expected status 303";
            }
            // find url in a single location header, as there should only be one
            const std::unordered_multimap<std::string, std::string>::const_iterator iter(response.headers().find(HEADER_LOCATION));
            if (iter == response.headers().end()) {
                // TODO: handle error (expected a header)
                return "error: expected a header";
            }
            
            return iter->second;
        }

        bool CredentialServiceImpl::register_credential(CredentialEndpointType type, const std::string& cred_id, const std::string& uri, const std::string& username, const std::string& secret) const {
            // TODO: implement
            return false;
        }

        std::vector<std::string> CredentialServiceImpl::credential_id_list(EndpointType type) const {
            // TODO: implement
            return std::vector<std::string>();
        }


        CredentialServiceImpl::~CredentialServiceImpl() = default;
    }
}