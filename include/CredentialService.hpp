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

    /**
     * Contains the endpoint types that can be registered with One Data Share by
     * providing One Data Share with the credentials needed to log into the
     * endpoint.
     */
    enum class CredentialEndpointType {
        SFTP, FTP, S3, HTTP
    };

    /**
     * Contains the endpoint types that can be registered with One Data Share
     * by using OAuth to give One Data Share permission to use the endpoint.
     */
    enum class OAuthEndpointType {
        DROPBOX, GOOGLE_DRIVE, BOX, GFTP
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