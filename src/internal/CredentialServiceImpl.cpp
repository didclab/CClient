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
            const std::string HEADER_CONTENT_TYPE("Content-Type");
            const std::string HEADER_JSON("application/json");
            const std::string HEADER_AUTHORIZATION("Authorization");
            const std::string HEADER_BEARER("Bearer: ");

            std::unordered_multimap<std::string, std::string> create_headers(const std::string& ods_auth_token) {
                std::unordered_multimap<std::string, std::string> headers;
                headers.insert(HEADER_CONTENT_TYPE, HEADER_JSON);
                headers.insert(HEADER_AUTHORIZATION, HEADER_BEARER + ods_auth_token);
            }
        }

        const std::string CredentialServiceImpl::API_PATH_OAUTH("/api/oauth");
        const std::string CredentialServiceImpl::API_PATH_CRED("/api/cred");


        CredentialServiceImpl::CredentialServiceImpl(const std::string& ods_auth_token, const std::string& ods_url, std::unique_ptr<rest::Rest> rest_caller) :
            _ods_auth_token(ods_auth_token),
            _ods_url(ods_url),
            _rest_caller(std::move(rest_caller)),
            _headers(create_headers(_ods_auth_token)) {
        }

        std::string CredentialService::oauth_url(OAuthEndpointType type) const {
            
        }

        CredentialServiceImpl::~CredentialServiceImpl() = default;
    }
}