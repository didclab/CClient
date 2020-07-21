/*
 * endpoint_impl.cpp
 * Andrew Mikalsen
 * 7/20/20
 */

#include <utility>

#include "endpoint_impl.h"

namespace One_data_share {

Endpoint_impl::Endpoint_impl(Endpoint_type type,
                             const std::string& cred_id,
                             const std::string& ods_oauth_token,
                             const std::string& ods_url,
                             std::unique_ptr<Rest> rest_caller)
    : type_(type),
      cred_id_(cred_id),
      ods_auth_token_(ods_oauth_token),
      ods_url_(ods_url),
      rest_caller_(std::move(rest_caller))
{}

std::unique_ptr<Resource> Endpoint_impl::list(const std::string& identifier) const
{
    // TODO: implement
    return nullptr;
}

void Endpoint_impl::remove(const std::string& identifier, const std::string& to_delete) const
{
    // TODO: implement
}

void Endpoint_impl::mkdir(const std::string& identifier, const std::string& folder_to_create) const
{
    // TODO: implement
}

void Endpoint_impl::download(const std::string& identifier, const std::string& file_to_download) const
{
    // TODO: implement
}

} // namespace One_data_share