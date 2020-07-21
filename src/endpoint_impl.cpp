/*
 * endpoint_impl.cpp
 * Andrew Mikalsen
 * 7/20/20
 */

#include <utility>

#include <onedatashare/ods_error.h>

#include "endpoint_impl.h"
#include "utils.h"

namespace One_data_share {

namespace {

constexpr auto api_path_box_list {"api/box/ls"};

constexpr auto api_path_dropbox_list {"/api/dropbox/ls"};

constexpr auto api_path_ftp_list {"/api/ftp/ls"};

constexpr auto api_path_google_drive_list {"/api/googledrive/list"};

constexpr auto api_path_gftp_list {"/api/gsiftp/ls"};

constexpr auto api_path_http_list {"/api/http/ls"};

constexpr auto api_path_s3_list {"/api/s3/ls"};

constexpr auto api_path_sftp_list {"/api/sftp/ls"};

/**
 * Returns the path for the list API call based on the specified endpoint type.
 *
 * @param type endpoint type to get the list API path for
 *
 * @return the list API path
 */
std::string select_list_path(Endpoint_type type)
{
    switch (type) {
    case Endpoint_type::dropbox:
        return api_path_dropbox_list;
    case Endpoint_type::google_drive:
        return api_path_google_drive_list;
    case Endpoint_type::sftp:
        return api_path_sftp_list;
    case Endpoint_type::ftp:
        return api_path_ftp_list;
    case Endpoint_type::box:
        return api_path_box_list;
    case Endpoint_type::s3:
        return api_path_s3_list;
    case Endpoint_type::gftp:
        return api_path_gftp_list;
    case Endpoint_type::http:
        return api_path_http_list;
    default:
        // TODO: throw exception
        return "";
    }
}

} // namespace

Endpoint_impl::Endpoint_impl(Endpoint_type type,
                             const std::string& cred_id,
                             const std::string& ods_oauth_token,
                             const std::string& ods_url,
                             std::unique_ptr<Rest> rest_caller)
    : type_ {type},
      cred_id_ {cred_id},
      ods_auth_token_ {ods_oauth_token},
      ods_url_ {ods_url},
      rest_caller_ {std::move(rest_caller)},
      headers_ {create_headers(ods_auth_token_)}
{}

std::unique_ptr<Resource> Endpoint_impl::list(const std::string& identifier) const
{
    // if get throws an expcetion, propagate it up
    auto response {rest_caller_->get(ods_url_ + select_list_path(type_), headers_)};

    if (response.status() != 200) {
        // unexpected response
        throw Unexpected_response_error {"Expected a 200 response code when listing resource \"" + identifier +
                                             "\" on endpoint \"" + cred_id_ + "\".",
                                         response.status()};
    }

    // TODO: implement
    return nullptr;
} // namespace One_data_share

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