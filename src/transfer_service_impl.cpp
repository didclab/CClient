/*
 * transfer_service_impl.cpp
 * Andrew Mikalsen
 * 7/23/20
 */

#include <utility>

#include "transfer_service_impl.h"
#include "utils.h"

namespace One_data_share {

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

std::unique_ptr<Transfer_status> Transfer_service_impl::status(const std::string& id) const
{
    // TODO: impl
    return nullptr;
}

} // namespace One_data_share