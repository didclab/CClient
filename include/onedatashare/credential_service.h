/*
 * credential_service.h
 * Andrew Mikalsen
 * 7/7/20
 */

#ifndef ONEDATASHARE_CREDENTIAL_SERVICE_H
#define ONEDATASHARE_CREDENTIAL_SERVICE_H

#include <memory>
#include <string>
#include <vector>

#include "endpoint_type.h"

namespace One_data_share {

/**
 * Contains the endpoint types that can be registered with One Data Share by providing One Data Share with the
 * credentials needed to log into the endpoint.
 */
enum class Credential_endpoint_type { sftp, ftp, s3, http };

/**
 * Contains the endpoint types that can be registered with One Data Share by using OAuth to give One Data Share
 * permission to use the endpoint.
 */
enum class Oauth_endpoint_type { dropbox, google_drive, box, gftp };

/**
 * Service providing all functionality related to registering credentials with One Data Share.
 */
class Credential_service {
public:
    /**
     * Creates a new Credential_service object with the specified authentication token, passing ownership of the
     * Credential_service object to the caller. It is expected that the specified authentication token is valid.
     *
     * @param ods_auth_token borrowed reference to the valid One Data Share authentication token to use
     *
     * @return a unique pointer to a new Credential_service object
     */
    static std::unique_ptr<Credential_service> create(const std::string& ods_auth_token);

    virtual ~Credential_service() = 0;

    Credential_service(const Credential_service&) = delete;

    Credential_service& operator=(const Credential_service&) = delete;

    Credential_service(Credential_service&&) = default;

    Credential_service& operator=(Credential_service&&) = default;

    /**
     * Gets the url that can be used to register an endpoint of the specified endpoint type with One Data Share via
     * OAuth. It is expected that the authentication token used to create this Credential_service object is valid
     * and that a connection can be made to One Data Share. If these preconditions are not met, exceptions may be
     * thrown.
     *
     * @param type the endpoint type to get the OAuth url for
     *
     * @return a string containing the OAuth url
     *
     * @exception Connection_error if unable to connect to One Data Share
     * @exception Unexpected_response_error if an unexpected response is received from One Data Share
     */
    virtual std::string oauth_url(Oauth_endpoint_type type) const = 0;

    /**
     * Registers the specified endpoint with One Data Share using the specified credentials. It is expected that the
     * authentication token used to create this Credential_service object is valid and that a connection can be made
     * to One Data Share. If these preconditions are not met, exceptions may be thrown.
     *
     * @param type the endpoint type to register
     * @param cred_id borrowed reference to the credential identifier to associate with the registered endpoint
     * @param uri borrowed reference to the uri of the endpoint to register
     * @param username borrowed pointer to the username needed to log in to the endpoint or nullptr to register an
     * endpoint without a username
     * @param secret borrowed pointer to the password needed to log in to the endpoint or nullptr to register an
     * endpoint without a password
     *
     * @exception Connection_error if unable to connect to One Data Share
     * @exception Unexpected_response_error if an unexpected response is received from One Data Share
     */
    virtual void register_credential(Credential_endpoint_type type,
                                     const std::string& cred_id,
                                     const std::string& uri,
                                     const std::string* username,
                                     const std::string* secret) const = 0;

    /**
     * Lists the credential identifiers of the specified endpoint type that are registered with One Data Share. It is
     * expected that the authenitcation token used to create this Credential_service object is valid and that a
     * connection can be made to One Data Share. If these preconditions are not met, exceptions may be thrown.
     *
     * @param type the endpoint type to list the registered credential identifiers of
     *
     * @return a vector of the registered credential identifiers for the sepcified endpoint
     *
     * @exception Connection_error if unable to connect to One Data Share
     * @exception Unexpected_response_error if an unexpected response is received from One Data Share
     */
    virtual std::vector<std::string> credential_id_list(Endpoint_type type) const = 0;

protected:
    Credential_service();
};

} // namespace One_data_share

#endif // ONEDATASHARE_CREDENTIAL_SERVICE_H