/*
 * endpoint.cpp
 * Andrew Mikalsen
 * 7/20/20
 */

#include <onedatashare/endpoint.h>

#include "curl_rest.h"
#include "endpoint_impl.h"
#include "utils.h"

namespace One_data_share {

Resource::Resource() = default;

Resource::~Resource() = default;

std::unique_ptr<Endpoint> Endpoint::create(Endpoint_type type,
                                           const std::string& cred_id,
                                           const std::string& ods_auth_token)
{
    // TODO: make this false in production build
    auto use_configured_ods_url = true;

    std::string ods_url {};
    if (use_configured_ods_url) {
        load_url_from_config(ods_url);
    } else {
        ods_url = get_ods_production_url();
    }

    return std::make_unique<Endpoint_impl>(type, cred_id, ods_auth_token, ods_url, std::make_unique<Curl_rest>());
}

Endpoint::Endpoint() = default;

Endpoint::~Endpoint() = default;

} // namespace One_data_share