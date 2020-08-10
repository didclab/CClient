/**
 * @file endpoint.cpp
 *
 * @author Andrew Mikalsen
 * @date 7/20/20
 */

#include <onedatashare/endpoint.h>

#include "curl_rest.h"
#include "endpoint_impl.h"
#include "util.h"

namespace One_data_share {

std::unique_ptr<Endpoint> Endpoint::create(Endpoint_type type,
                                           const std::string& cred_id,
                                           const std::string& ods_auth_token)
{
    return create(type, cred_id, ods_auth_token, Internal::Util::ods_production_url);
}

std::unique_ptr<Endpoint> Endpoint::create(Endpoint_type type,
                                           const std::string& cred_id,
                                           const std::string& ods_auth_token,
                                           const std::string& url)
{
    return std::make_unique<Internal::Endpoint_impl>(type,
                                                     cred_id,
                                                     ods_auth_token,
                                                     url,
                                                     std::make_unique<Internal::Curl_rest>());
}

Endpoint::Endpoint() = default;

Endpoint::~Endpoint() = default;

} // namespace One_data_share
