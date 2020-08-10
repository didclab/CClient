/**
 * @file endpoint_impl.h
 * Defines the internal implementation of classes needed to interact with an endpoint's file sytem.
 *
 * @author Andrew Mikalsen
 * @date 7/20/20
 */

#ifndef ONEDATASHARE_ENDPOINT_IMPL_H
#define ONEDATASHARE_ENDPOINT_IMPL_H

#include <memory>
#include <string>
#include <unordered_map>

#include <onedatashare/endpoint.h>
#include <onedatashare/endpoint_type.h>

#include "rest.h"

namespace One_data_share {
namespace Internal {

/**
 * Service that makes REST API calls to One Data Share related to an endpoint's file system.
 */
class Endpoint_impl : public Endpoint {
public:
    /**
     * Creates a new Endpoint_impl object for the specified endpoint with the specified connection to One Data Share
     * using the specified rest caller.
     *
     * @param type the type of endpoint to return
     * @param cred_id borrowed reference to the credential id of the endpoint to use
     * @param ods_auth_token borrowed reference to the One Data Share authentication token to use
     * @param ods_url borrowed reference to the url that One Data Share is running on
     * @param rest_caller moved pointer to the object to use for making REST API calls
     */
    Endpoint_impl(Endpoint_type type,
                  const std::string& cred_id,
                  const std::string& ods_oauth_token,
                  const std::string& ods_url,
                  std::unique_ptr<Rest> rest_caller);

    Resource list(const std::string& identifier) const override;

    void remove(const std::string& identifier, const std::string& to_delete) const override;

    void mkdir(const std::string& identifier, const std::string& folder_to_create) const override;

    void download(const std::string& identifier, const std::string& file_to_download) const override;

private:
    /** Type of the endpoint used in REST API calls. */
    const Endpoint_type type_;

    /** Credential id of the endpoint used in REST API calls. */
    const std::string cred_id_;

    /** One Data Share authentication token used in REST API calls. */
    const std::string ods_auth_token_;

    /** Url to the One Data Share server to make REST API calls to. */
    const std::string ods_url_;

    /** Pointer to the object used to make REST API calls. */
    const std::unique_ptr<Rest> rest_caller_;

    /** Headers used in REST API calls. */
    const std::unordered_multimap<std::string, std::string> headers_;
};

} // namespace Internal
} // namespace One_data_share

#endif // ONEDATASHARE_ENDPOINT_IMPL_H
