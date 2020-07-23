/*
 * transfer_service_impl.cpp
 * Andrew Mikalsen
 * 7/23/20
 */

#include <utility>

#include "transfer_service_impl.h"
#include "utils.h"

namespace One_data_share {

Destination_impl::Destination_impl(Endpoint_type type,
                                   const std::string& cred_id,
                                   const std::string& directory_identifier)
    : type_(type),
      cred_id_(cred_id),
      directory_identifier_(directory_identifier)
{}

Source_impl::Source_impl(Endpoint_type type,
                         const std::string& cred_id,
                         const std::string& directory_identifier,
                         const std::vector<std::string>& resource_identifiers)
    : type_(type),
      cred_id_(cred_id),
      directory_identifier_(directory_identifier),
      resource_identifiers_(resource_identifiers)
{}

Transfer_service_impl::Transfer_service_impl(const std::string& ods_auth_token,
                                             const std::string& ods_url,
                                             std::unique_ptr<Rest> rest_caller)
    : ods_auth_token_(ods_auth_token),
      ods_url_(ods_url),
      rest_caller_(std::move(rest_caller)),
      headers_(create_headers(ods_auth_token_))
{}

std::string Transfer_service_impl::transfer(const Source& source,
                                            const Destination& destination,
                                            const Transfer_options& options) const
{
    // TODO: impl
    return "";
}

std::unique_ptr<Transfer_status> Transfer_service::status(const std::string& id) const
{
    // TODO: impl
    return nullptr;
}

} // namespace One_data_share