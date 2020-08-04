/*
 * transfer_service.cpp
 * Andrew Mikalsen
 * 7/23/20
 */

#include <onedatashare/transfer_service.h>

#include "curl_rest.h"
#include "transfer_service_impl.h"
#include "utils.h"

namespace One_data_share {

Destination::Destination(Endpoint_type type, const std::string& cred_id, const std::string& directory_identifier)
    : type(type),
      cred_id(cred_id),
      directory_identifier(directory_identifier)
{}

Source::Source(Endpoint_type type,
               const std::string& cred_id,
               const std::string& directory_identifier,
               const std::vector<std::string>& resource_identifiers)
    : type(type),
      cred_id(cred_id),
      directory_identifier(directory_identifier),
      resource_identifiers(resource_identifiers)
{}

Transfer_options::Transfer_options() = default;

std::unique_ptr<Transfer_service> Transfer_service::create(const std::string& ods_auth_token)
{
    return create(ods_auth_token, Internal::get_ods_production_url());
}

std::unique_ptr<Transfer_service> Transfer_service::create(const std::string& ods_auth_token, const std::string& url)
{
    return std::make_unique<Internal::Transfer_service_impl>(ods_auth_token,
                                                             url,
                                                             std::make_unique<Internal::Curl_rest>());
}

Transfer_service::Transfer_service() = default;
Transfer_service::~Transfer_service() = default;

} // namespace One_data_share