/**
 * @file credential_service.cpp
 *
 * @author Andrew Mikalsen
 * @date 7/9/20
 */

#include <onedatashare/credential_service.h>

#include "credential_service_impl.h"
#include "curl_rest.h"
#include "utils.h"

namespace One_data_share {

std::unique_ptr<Credential_service> Credential_service::create(const std::string& ods_auth_token)
{
    return create(ods_auth_token, Internal::ods_production_url);
}

std::unique_ptr<Credential_service> Credential_service::create(const std::string& ods_auth_token,
                                                               const std::string& url)
{
    return std::make_unique<Internal::Credential_service_impl>(ods_auth_token,
                                                               url,
                                                               std::make_unique<Internal::Curl_rest>());
}

Credential_service::Credential_service() = default;

Credential_service::~Credential_service() = default;

} // namespace One_data_share
