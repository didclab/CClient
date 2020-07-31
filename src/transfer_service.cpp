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

Destination Destination::create(Endpoint_type type, const std::string& cred_id, const std::string& directory_identifier)
{
    return Destination {type, cred_id, directory_identifier};
}

Destination::Destination(Endpoint_type type, const std::string& cred_id, const std::string& directory_identifier)
    : type_(type),
      cred_id_(cred_id),
      directory_identifier_(directory_identifier)
{}

Endpoint_type Destination::type() const
{
    return type_;
}

const std::string& Destination::cred_id() const
{
    return cred_id_;
}

const std::string& Destination::directory_identifier() const
{
    return directory_identifier_;
}

Source Source::create(Endpoint_type type,
                      const std::string& cred_id,
                      const std::string& directory_identifier,
                      const std::vector<std::string>& resource_identifiers)
{
    return Source(type, cred_id, directory_identifier, resource_identifiers);
}

Source::Source(Endpoint_type type,
               const std::string& cred_id,
               const std::string& directory_identifier,
               const std::vector<std::string>& resource_identifiers)
    : type_(type),
      cred_id_(cred_id),
      directory_identifier_(directory_identifier),
      resource_identifiers_(resource_identifiers)
{}

Endpoint_type Source::type() const
{
    return type_;
}

const std::string& Source::cred_id() const
{
    return cred_id_;
}

const std::string& Source::directory_identifier() const
{
    return directory_identifier_;
}

const std::vector<std::string>& Source::resource_identifiers() const
{
    return resource_identifiers_;
}

Transfer_options Transfer_options::create()
{
    return Transfer_options {};
}

Transfer_options::Transfer_options() = default;

Transfer_status::Transfer_status() = default;
Transfer_status::~Transfer_status() = default;

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