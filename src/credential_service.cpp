/*
 * credential_service.cpp
 * Andrew Mikalsen
 * 7/9/20
 */

#include <fstream>

#include <onedatashare/credential_service.h>

#include "credential_service_impl.h"
#include "curl_rest.h"

namespace One_data_share {

namespace {

constexpr auto url_config_file_location {"url.txt"};
constexpr auto deployed_ods_url {"https://onedatashare.org"};

/**
 * Sets the url in the config file to the specified string.
 *
 * @param url mutably borrowed reference to the string to set the read url to
 *
 * @return true if and only if the config file was found and could be opened
 */
bool load_url_from_config(std::string& url)
{
    std::ifstream file {url_config_file_location};
    if (!file.is_open()) {
        return false;
    }
    std::getline(file, url);

    file.close();
    return true;
}

} // namespace

std::unique_ptr<Credential_service> Credential_service::create(const std::string& ods_auth_token)
{
    auto use_configured_ods_url = true;

    std::string ods_url {};
    if (use_configured_ods_url) {
        load_url_from_config(ods_url);
    } else {
        ods_url = deployed_ods_url;
    }

    return std::make_unique<Credential_service_impl>(ods_auth_token, ods_url, std::make_unique<Curl_rest>());
}

Credential_service::Credential_service() = default;

Credential_service::~Credential_service() = default;

} // namespace One_data_share