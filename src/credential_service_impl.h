/*
 * credential_service_impl.h
 * Andrew Mikalsen
 * 7/9/20
 */

#ifndef ONEDATASHARE_CREDENTIAL_SERVICE_IMPL_H
#define ONEDATASHARE_CREDENTIAL_SERVICE_IMPL_H

#include <memory>
#include <string>
#include <unordered_map>

#include <onedatashare/credential_service.h>
#include <onedatashare/endpoint_type.h>

#include "rest.h"

namespace One_data_share {

namespace Internal {

/**
 * Service that makes REST API calls to One Data Share related to registering credentials.
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

    ~Credential_service_impl() override = default;

    Credential_service_impl(const Credential_service_impl&) = delete;

    Credential_service_impl& operator=(const Credential_service_impl&) = delete;

    Credential_service_impl(Credential_service_impl&&) = default;

    Credential_service_impl& operator=(Credential_service_impl&&) = default;

    std::string oauth_url(Oauth_endpoint_type type) const override;

    void register_credential(Credential_endpoint_type type,
                             const std::string& cred_id,
                             const std::string& uri,
                             const std::string* username,
                             const std::string* secret) const override;

    std::vector<std::string> credential_id_list(Endpoint_type type) const override;

private:
    /**
     * One Data Share authentication token used in REST API calls.
     */
    const std::string ods_auth_token_;

    /**
     * Url to the One Data Share server to make REST API calls to.
     */
    const std::string ods_url_;

    /**
     * Pointer to the object used to make REST API calls.
     */
    const std::unique_ptr<Rest> rest_caller_;

    /**
     * Headers used in REST API calls.
     */
    const std::unordered_multimap<std::string, std::string> headers_;
};

} // namespace Internal

} // namespace One_data_share

#endif // ONEDATASHARE_CREDENTIAL_SERVICE_IMPL_H