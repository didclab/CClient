/*
 * CredentialService.hpp
 * Andrew Mikalsen
 * 7/7/20
 */

#ifndef CREDENTIAL_SERVICE_HPP_INCLUDED
#define CREDENTIAL_SERVICE_HPP_INCLUDED

#include <string>
#include <EndpointType.hpp>

namespace ods {

    enum class CredentialEndpointType {

    };

    enum class OAuthEndpointType {

    };

    /**
     * Service providing all functionality related to registering credentials
     * with One Data Share.
     */
    class CredentialService {
        public:
            virtual std::string oauth_link(OAuthEndpointType type) = 0;

            CredentialService(const CredentialService&) = delete;
            CredentialService& operator=(const CredentialService&) = delete;

            virtual ~CredentialService() = 0;
        private:
            CredentialService() = default;
    };
}

#endif // CREDENTIAL_SERVICE_HPP_INCLUDED