/**
 * @file credential_service_impl.h
 * Defines the internal implementation of classes needed to regsiter credentials.
 *
 * @author Andrew Mikalsen
 * @date 7/9/20
 */

#ifndef ONEDATASHARE_CREDENTIAL_SERVICE_IMPL_H
#define ONEDATASHARE_CREDENTIAL_SERVICE_IMPL_H

#include <memory>
#include <string>
#include <unordered_map>

#include <onedatashare/credential_service.h>
#include <onedatashare/endpoint_type.h>

#include "rest.h"

namespace Onedatashare {
namespace Internal {

/**
 * Service that makes REST API calls to OneDataShare related to registering credentials.
 */
class Credential_service_impl : public Credential_service {
public:
    /**
     * Creates a new Credential_service_impl object with the specified token, url, and rest caller.
     *
     * @param ods_auth_token borrowed reference to the token to use for REST API calls
     * @param ods_url borrowed reference to the url to make REST API calls to
     * @param rest_caller moved pointer to object to use for making REST API calls
     */
    Credential_service_impl(const std::string& ods_auth_token,
                            const std::string& ods_url,
                            std::unique_ptr<Rest> rest_caller);

    /**
     * Makes a REST API call to get the OAuth url needed to register an endpoint of the specified type.
     *
     * @param type the endpoint type to get the OAuth url for
     *
     * @return a string containing the OAuth url
     *
     * @exception Connection_error if unable to connect to OneDataShare
     * @exception Unexpected_response_error if an unexpected response is received from OneDataShare
     */
    std::string oauth_url(Oauth_endpoint_type type) const override;

    /**
     * Makes a REST API call to register the specified credentials.
     *
     * @param type the endpoint type to register
     * @param cred_id borrowed reference to the credential identifier to associate with the registered endpoint
     * @param uri borrowed reference to the uri of the endpoint to register
     * @param username borrowed pointer to the username needed to log in to the endpoint or nullptr to register an
     * endpoint without a username
     * @param secret borrowed pointer to the password needed to log in to the endpoint or nullptr to register an
     * endpoint without a password
     *
     * @exception Connection_error if unable to connect to OneDataShare
     * @exception Unexpected_response_error if an unexpected response is received from OneDataShare
     */
    void register_credential(Credential_endpoint_type type,
                             const std::string& cred_id,
                             const std::string& uri,
                             const std::string* username,
                             const std::string* secret) const override;

    /**
     * Makes a REST API call to get the list of credential identifiers of the specified type that are registered.
     *
     * @param type the endpoint type to list the registered credential identifiers of
     *
     * @return a vector of the registered credential identifiers for the sepcified endpoint
     *
     * @exception Connection_error if unable to connect to OneDataShare
     * @exception Unexpected_response_error if an unexpected response is received from OneDataShare
     */
    std::vector<std::string> credential_id_list(Endpoint_type type) const override;

private:
    /** Url to the OneDataShare server to make REST API calls to. */
    const std::string ods_url_;

    /** Pointer to the object used to make REST API calls. */
    const std::unique_ptr<Rest> rest_caller_;

    /** Headers used in REST API calls. */
    const std::unordered_multimap<std::string, std::string> headers_;
};

} // namespace Internal
} // namespace Onedatashare

#endif // ONEDATASHARE_CREDENTIAL_SERVICE_IMPL_H
