/*
 * CredentialService.hpp
 * Andrew Mikalsen
 * 7/7/20
 */

#ifndef CREDENTIAL_SERVICE_HPP_INCLUDED
#define CREDENTIAL_SERVICE_HPP_INCLUDED

#include <memory>
#include <string>
#include <vector>
#include "EndpointType.hpp"

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
     * with One Data Share. CredentialService objects cannot be copied via their copy 
     * constructor nor their copy assignment operator.
     */
    class CredentialService {
        public:
            /**
             * Creates a new CredentialService object with the specified
             * authentication token, passing ownership of the CredentialService
             * object to the caller.
             * 
             * @param ods_auth_token the One Data Share authentication token to
             * use
             * 
             * @return a unique pointer to a new CredentialService object
             */
            static std::unique_ptr<CredentialService> create(std::string ods_auth_token);

            /**
             * Gets the url that can be used to register an endpoint of the
             * specified endpoint type with One Data Share via OAuth.
             * 
             * @param type the endpoint type to get the OAuth url for
             * 
             * @return a string containing the OAuth url
             */
            virtual std::string oauth_url(OAuthEndpointType type) const = 0;

            /**
             * Registers the specified endpoint with One Data Share using the
             * specified credentials.
             * 
             * @param type the endpoint type to register
             * @param cred_id borrowed reference to the credential identifier
             * to associate with the registered endpoint
             * @param uri borrowed reference to the uri of the endpoint to
             * register
             * @param username borrowed reference to the username needed to log
             * in to the endpoint
             * @param secret borrowed reference to the password needed to log in
             * to the endpoint
             * 
             * @return true if and only if this operation successfully
             * registered the endpoint with the specified credentials
             */
            virtual bool register_credential(CredentialEndpointType type, const std::string& cred_id, const std::string& uri, const std::string& username, const std::string& secret) const = 0;

            /**
             * Lists the credential identifiers of the specified endpoint type
             * that are registered with One Data Share.
             * 
             * @param type the endpoint type to list the registered credential
             * identifiers of
             * 
             * @return a vector of the registered credential identifiers for the
             * sepcified endpoint
             */
            virtual std::vector<std::string> credential_id_list(EndpointType type) const = 0;

            CredentialService(const CredentialService&) = delete;
            CredentialService& operator=(const CredentialService&) = delete;

            virtual ~CredentialService() = 0;
        protected:
            CredentialService();
    };
}

#endif // CREDENTIAL_SERVICE_HPP_INCLUDED