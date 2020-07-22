/*
 * credential_service.cpp
 * Andrew Mikalsen
 * 7/9/20
 */

#include <onedatashare/credential_service.h>

#include "credential_service_impl.h"
#include "curl_rest.h"
#include "utils.h"

namespace One_data_share {

std::unique_ptr<Credential_service> Credential_service::create(const std::string& ods_auth_token)
{
    // TODO: make this false in production build
    auto use_configured_ods_url = true;

    std::string ods_url {};
    if (use_configured_ods_url) {
        load_url_from_config(ods_url);
    } else {
        ods_url = get_ods_production_url();
    }

    return std::make_unique<Credential_service_impl>(ods_auth_token, ods_url, std::make_unique<Curl_rest>());
}

Credential_service::Credential_service() = default;

Credential_service::~Credential_service() = default;

} // namespace One_data_share