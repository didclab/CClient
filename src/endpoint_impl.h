/*
 * endpoint_impl.h
 * Andrew Mikalsen
 * 7/20/20
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

class Endpoint_impl : public Endpoint {
public:
    Endpoint_impl(Endpoint_type type,
                  const std::string& cred_id,
                  const std::string& ods_oauth_token,
                  const std::string& ods_url,
                  std::unique_ptr<Rest> rest_caller);

    virtual ~Endpoint_impl() = default;

    Endpoint_impl(const Endpoint_impl&) = delete;

    Endpoint_impl& operator=(const Endpoint_impl&) = delete;

    Endpoint_impl(Endpoint_impl&&) = default;

    Endpoint_impl& operator=(Endpoint_impl&&) = default;

    virtual std::unique_ptr<Resource> list(const std::string& identifier) const;

    virtual void remove(const std::string& identifier, const std::string& to_delete) const;

    virtual void mkdir(const std::string& identifier, const std::string& folder_to_create) const;

    virtual void download(const std::string& identifier, const std::string& file_to_download) const;

private:
    /**
     * Type of the endpoint used in REST API calls.
     */
    const Endpoint_type type_;

    /**
     * Credential id of the endpoint used in REST API calls.
     */
    const std::string cred_id_;

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

} // namespace One_data_share

#endif // ONEDATASHARE_ENDPOINT_IMPL_H