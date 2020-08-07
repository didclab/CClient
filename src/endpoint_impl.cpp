/*
 * endpoint_impl.cpp
 * Andrew Mikalsen
 * 7/20/20
 */

#include <optional>
#include <sstream>
#include <utility>
#include <vector>

#include <simdjson/simdjson.h>

#include <onedatashare/ods_error.h>

#include "endpoint_impl.h"
#include "utils.h"

namespace One_data_share {

namespace Internal {

namespace {

constexpr auto api_path_box_list {"api/box/ls"};
constexpr auto api_path_dropbox_list {"/api/dropbox/ls"};
constexpr auto api_path_ftp_list {"/api/ftp/ls"};
constexpr auto api_path_google_drive_list {"/api/googledrive/ls"};
constexpr auto api_path_gftp_list {"/api/gsiftp/ls"};
constexpr auto api_path_http_list {"/api/http/ls"};
constexpr auto api_path_s3_list {"/api/s3/ls"};
constexpr auto api_path_sftp_list {"/api/sftp/ls"};

constexpr auto api_path_box_rm {"api/box/rm"};
constexpr auto api_path_dropbox_rm {"/api/dropbox/rm"};
constexpr auto api_path_ftp_rm {"/api/ftp/rm"};
constexpr auto api_path_google_drive_rm {"/api/googledrive/rm"};
constexpr auto api_path_gftp_rm {"/api/gsiftp/rm"};
constexpr auto api_path_http_rm {"/api/http/rm"};
constexpr auto api_path_s3_rm {"/api/s3/rm"};
constexpr auto api_path_sftp_rm {"/api/sftp/rm"};

constexpr auto api_path_box_mkdir {"api/box/mkdir"};
constexpr auto api_path_dropbox_mkdir {"/api/dropbox/mkdir"};
constexpr auto api_path_ftp_mkdir {"/api/ftp/mkdir"};
constexpr auto api_path_google_drive_mkdir {"/api/googledrive/mkdir"};
constexpr auto api_path_gftp_mkdir {"/api/gsiftp/mkdir"};
constexpr auto api_path_http_mkdir {"/api/http/mkdir"};
constexpr auto api_path_s3_mkdir {"/api/s3/mkdir"};
constexpr auto api_path_sftp_mkdir {"/api/sftp/mkdir"};

constexpr auto api_path_box_download {"api/box/download"};
constexpr auto api_path_dropbox_download {"/api/dropbox/download"};
constexpr auto api_path_ftp_download {"/api/ftp/download"};
constexpr auto api_path_google_drive_download {"/api/googledrive/download"};
constexpr auto api_path_gftp_download {"/api/gsiftp/download"};
constexpr auto api_path_http_download {"/api/http/download"};
constexpr auto api_path_s3_download {"/api/s3/download"};
constexpr auto api_path_sftp_download {"/api/sftp/download"};

constexpr auto stat_id {"id"};
constexpr auto stat_name {"name"};
constexpr auto stat_size {"size"};
constexpr auto stat_time {"time"};
constexpr auto stat_dir {"dir"};
constexpr auto stat_file {"file"};
constexpr auto stat_link {"link"};
constexpr auto stat_permissions {"permissions"};
constexpr auto stat_files {"files"};

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

/**
 * Gets the remove api path for the sepcified type.
 *
 * @param type endpoint to get the api path for
 *
 * @return the api path
 */
std::string select_rm_path(Endpoint_type type)
{
    switch (type) {
    case Endpoint_type::dropbox:
        return api_path_dropbox_rm;
    case Endpoint_type::google_drive:
        return api_path_google_drive_rm;
    case Endpoint_type::sftp:
        return api_path_sftp_rm;
    case Endpoint_type::ftp:
        return api_path_ftp_rm;
    case Endpoint_type::box:
        return api_path_box_rm;
    case Endpoint_type::s3:
        return api_path_s3_rm;
    case Endpoint_type::gftp:
        return api_path_gftp_rm;
    case Endpoint_type::http:
        return api_path_http_rm;
    default:
        // TODO: throw exception
        return "";
    }
}

/**
 * Gets the mkdir api path for the specified type.
 *
 * @param type endpoint to get the api path for
 *
 * @return the api path
 */
std::string select_mkdir_path(Endpoint_type type)
{
    switch (type) {
    case Endpoint_type::dropbox:
        return api_path_dropbox_mkdir;
    case Endpoint_type::google_drive:
        return api_path_google_drive_mkdir;
    case Endpoint_type::sftp:
        return api_path_sftp_mkdir;
    case Endpoint_type::ftp:
        return api_path_ftp_mkdir;
    case Endpoint_type::box:
        return api_path_box_mkdir;
    case Endpoint_type::s3:
        return api_path_s3_mkdir;
    case Endpoint_type::gftp:
        return api_path_gftp_mkdir;
    case Endpoint_type::http:
        return api_path_http_mkdir;
    default:
        // TODO: throw exception
        return "";
    }
}

/**
 * Gets the download api path for the specified type.
 *
 * @param type endpoint to get the api path for
 *
 * @return the api path
 */
std::string select_download_path(Endpoint_type type)
{
    switch (type) {
    case Endpoint_type::dropbox:
        return api_path_dropbox_download;
    case Endpoint_type::google_drive:
        return api_path_google_drive_download;
    case Endpoint_type::sftp:
        return api_path_sftp_download;
    case Endpoint_type::ftp:
        return api_path_ftp_download;
    case Endpoint_type::box:
        return api_path_box_download;
    case Endpoint_type::s3:
        return api_path_s3_download;
    case Endpoint_type::gftp:
        return api_path_gftp_download;
    case Endpoint_type::http:
        return api_path_http_download;
    default:
        // TODO: throw exception
        return "";
    }
}

/**
 * Creates a Resource object containing the data stored in the specified Stat json object. It is expected that the
 * specified dom conforms to the Stat object specifications.
 *
 * @param obj borrowed reference to the dom containing the Stat json object to parse
 *
 * @return the Resource created from parsing the specified dom
 *
 * @throw simdjson_error if simdjson encounters an error parsing the dom
 */
Resource create_resource(const simdjson::dom::object& obj)
{
    // keep track of errors that can be handled, propogate errors that indicate a malformed response
    auto [id_elm, id_err] {obj[stat_id]};
    auto name {obj[stat_name]};
    auto size {obj[stat_size]};
    auto time {obj[stat_time]};
    auto dir {obj[stat_dir]};
    auto file {obj[stat_file]};
    auto [link_elm, link_err] {obj[stat_link]};
    auto [permissions_elm, permissions_err] {obj[stat_permissions]};
    auto [files_elm, files_err] {obj[stat_files]};

    // recursively add contained resoruces
    std::vector<Resource> contained {};
    if (!files_err) {
        for (const auto& r : files_elm) {
            // propogate up simdjson_error if thrown
            contained.push_back(create_resource(r.get_object().take_value()));
        }
    }

    return {id_err ? std::nullopt : std::optional {id_elm.get_c_str().take_value()},
            name.get_c_str().take_value(),
            size.get_int64().take_value(),
            time.get_int64().take_value(),
            dir.get_bool().take_value(),
            file.get_bool().take_value(),
            link_err ? std::nullopt : std::optional {link_elm.get_c_str().take_value()},
            permissions_err ? std::nullopt : std::optional {permissions_elm.get_c_str().take_value()},
            files_err ? std::nullopt : std::optional {contained}};
}

/**
 * Creates a DeleteOperation json object with the specified fields.
 */
std::string create_delete_operation(const std::string& cred_id,
                                    const std::string& path,
                                    const std::string& id,
                                    const std::string& to_delete)
{
    std::ostringstream stream {};
    stream << "{\"credId\":\"" << escape_json(cred_id) << "\",\"path\":\"" << escape_json(path) << "\",\"id\":\""
           << escape_json(id) << "\",\"toDelete\":\"" << escape_json(to_delete) << "\"}";

    return stream.str();
}

/**
 * Creates a MkdirOperation json object with the specified fields.
 */
std::string create_mkdir_operation(const std::string& cred_id,
                                   const std::string& path,
                                   const std::string& id,
                                   const std::string& folder_to_create)
{
    std::ostringstream stream {};
    stream << "{\"credId\":\"" << escape_json(cred_id) << "\",\"path\":\"" << escape_json(path) << "\",\"id\":\""
           << escape_json(id) << "\",\"folderToCreate\":\"" << escape_json(folder_to_create) << "\"}";

    return stream.str();
}

/**
 * Creates a DownloadOperation json object with the specified fields.
 */
std::string create_download_operation(const std::string& cred_id,
                                      const std::string& path,
                                      const std::string& id,
                                      const std::string& file_to_download)
{
    std::ostringstream stream {};
    stream << "{\"credId\":\"" << escape_json(cred_id) << "\",\"path\":\"" << escape_json(path) << "\",\"id\":\""
           << escape_json(id) << "\",\"fileToDownload\":\"" << escape_json(file_to_download) << "\"}";

    return stream.str();
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

Resource Endpoint_impl::list(const std::string& identifier) const
{
    // if get throws an expcetion, propagate it up
    auto response {rest_caller_->get(ods_url_ + select_list_path(type_) + "?credId=" + cred_id_ +
                                         "&path=" + identifier + "&identifier=" + identifier,
                                     headers_)};

    if (response.status != 200) {
        // unexpected response
        throw Unexpected_response_error {"Expected a 200 response code when listing resource \"" + identifier +
                                             "\" on endpoint \"" + cred_id_ + "\".",
                                         response.status};
    }

    simdjson::dom::parser parser {};
    auto [obj, err] {parser.parse(response.body).get_object()};

    if (err) {
        // bad response body
        throw Unexpected_response_error {"Error parsing json recieved after listing resource \"" + identifier +
                                             "\" on endpoint \"" + cred_id_ + "\": " + simdjson::error_message(err),
                                         response.status};
    }

    Resource resource {};
    try {
        resource = create_resource(obj);
    } catch (simdjson::simdjson_error e) {
        // bad response body
        throw Unexpected_response_error {"Error parsing json recieved after listing resource \"" + identifier +
                                             "\" on endpoint \"" + cred_id_ + "\": " + e.what(),
                                         response.status};
    }

    if (!resource.contained_resources && resource.is_directory) {
        // bad response body
        throw Unexpected_response_error {
            "Parsed resource was a directory but didn't have contained resources when listing resource \"" +
                identifier + "\" on endpoint \"" + cred_id_ + "\".",
            response.status};
    }

    if (!resource.id && (type_ == Endpoint_type::box || type_ == Endpoint_type::google_drive)) {
        // bad response body
        throw Unexpected_response_error {"Expected parsed resource to have an id.", response.status};
    }

    return resource;
}

void Endpoint_impl::remove(const std::string& identifier, const std::string& to_delete) const
{
    // if post throws an expcetion, propagate it up
    auto response {rest_caller_->post(ods_url_ + select_rm_path(type_),
                                      headers_,
                                      create_delete_operation(cred_id_, identifier, identifier, to_delete))};

    if (response.status != 200) {
        // expected status 200
        throw Unexpected_response_error {"Expected a status 200 response after removing resource.", response.status};
    }
}

void Endpoint_impl::mkdir(const std::string& identifier, const std::string& folder_to_create) const
{
    // if post throws an expcetion, propagate it up
    auto response {rest_caller_->post(ods_url_ + select_mkdir_path(type_),
                                      headers_,
                                      create_mkdir_operation(cred_id_, identifier, identifier, folder_to_create))};

    if (response.status != 200) {
        // expected status 200
        throw Unexpected_response_error {"Expected a status 200 response after creating directory.", response.status};
    }
}

void Endpoint_impl::download(const std::string& identifier, const std::string& file_to_download) const
{
    // if post throws an expcetion, propagate it up
    auto response {rest_caller_->post(ods_url_ + select_download_path(type_),
                                      headers_,
                                      create_download_operation(cred_id_, identifier, identifier, file_to_download))};

    if (response.status != 200) {
        // expected status 200
        throw Unexpected_response_error {"Expected a status 200 response after downloading resource.", response.status};
    }
}

} // namespace Internal

} // namespace One_data_share