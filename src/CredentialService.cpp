/*
 * CredentialService.cpp
 * Andrew Mikalsen
 * 7/9/20
 */

#include <CredentialService.hpp>
#include "internal/CredentialServiceImpl.hpp"
#include "rest/CurlRest.hpp"
#include "util.hpp"

namespace ods {
    std::unique_ptr<CredentialService> CredentialService::create(const std::string& ods_auth_token) {
        bool use_configured_ods_url = true;

        std::string ods_url;
        if (use_configured_ods_url) {
            util::load_url_from_config(ods_url);
        } else {
            ods_url = util::ODS_URL;
        }

        return std::make_unique<internal::CredentialServiceImpl>(ods_auth_token, ods_url, std::make_unique<rest::CurlRest>());
    }

    CredentialService::CredentialService() = default;
    CredentialService::~CredentialService() = default;
}