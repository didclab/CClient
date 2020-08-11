/**
 * @file endpoint_impl.cpp
 *
 * @author Andrew Mikalsen
 * @date 7/20/20
 */

#include <optional>
#include <sstream>
#include <utility>
#include <vector>

#include <simdjson/simdjson.h>

#include <onedatashare/ods_error.h>

#include "endpoint_impl.h"
#include "error_message.h"
#include "ods_rest_api.h"
#include "util.h"

namespace One_data_share {
namespace Internal {

namespace {

/**
 * Gets the list api path for the sepcified type.
 *
 * @param type endpoint to get the api path for
 *
 * @return the api path
 *
 * @exception invalid_argument if passed an invalid Endpoint_type value
 */
std::string select_list_path(Endpoint_type type)
{
    switch (type) {
    case Endpoint_type::dropbox:
        return Api::dropbox_ls_path;
    case Endpoint_type::google_drive:
        return Api::google_drive_ls_path;
    case Endpoint_type::sftp:
        return Api::sftp_ls_path;
    case Endpoint_type::ftp:
        return Api::ftp_ls_path;
    case Endpoint_type::box:
        return Api::box_ls_path;
    case Endpoint_type::s3:
        return Api::s3_ls_path;
    case Endpoint_type::gftp:
        return Api::gftp_ls_path;
    case Endpoint_type::http:
        return Api::http_ls_path;
    }

    throw std::invalid_argument(Err::unknown_enum_msg);
}

/**
 * Gets the remove api path for the sepcified type.
 *
 * @param type endpoint to get the api path for
 *
 * @return the api path
 *
 * @exception invalid_argument if passed an invalid Endpoint_type value
 */
std::string select_rm_path(Endpoint_type type)
{
    switch (type) {
    case Endpoint_type::dropbox:
        return Api::dropbox_rm_path;
    case Endpoint_type::google_drive:
        return Api::google_drive_rm_path;
    case Endpoint_type::sftp:
        return Api::sftp_rm_path;
    case Endpoint_type::ftp:
        return Api::ftp_rm_path;
    case Endpoint_type::box:
        return Api::box_rm_path;
    case Endpoint_type::s3:
        return Api::s3_rm_path;
    case Endpoint_type::gftp:
        return Api::gftp_rm_path;
    case Endpoint_type::http:
        return Api::http_rm_path;
    }

    throw std::invalid_argument(Err::unknown_enum_msg);
}

/**
 * Gets the mkdir api path for the specified type.
 *
 * @param type endpoint to get the api path for
 *
 * @return the api path
 *
 * @exception invalid_argument if passed an invalid Endpoint_type value
 */
std::string select_mkdir_path(Endpoint_type type)
{
    switch (type) {
    case Endpoint_type::dropbox:
        return Api::dropbox_mkdir_path;
    case Endpoint_type::google_drive:
        return Api::google_drive_mkdir_path;
    case Endpoint_type::sftp:
        return Api::sftp_mkdir_path;
    case Endpoint_type::ftp:
        return Api::ftp_mkdir_path;
    case Endpoint_type::box:
        return Api::box_mkdir_path;
    case Endpoint_type::s3:
        return Api::s3_mkdir_path;
    case Endpoint_type::gftp:
        return Api::gftp_mkdir_path;
    case Endpoint_type::http:
        return Api::http_mkdir_path;
    }

    throw std::invalid_argument(Err::unknown_enum_msg);
}

/**
 * Gets the download api path for the specified type.
 *
 * @param type endpoint to get the api path for
 *
 * @return the api path
 *
 * @exception invalid_argument if passed an invalid Endpoint_type value
 */
std::string select_download_path(Endpoint_type type)
{
    switch (type) {
    case Endpoint_type::dropbox:
        return Api::dropbox_download_path;
    case Endpoint_type::google_drive:
        return Api::google_drive_download_path;
    case Endpoint_type::sftp:
        return Api::sftp_download_path;
    case Endpoint_type::ftp:
        return Api::ftp_download_path;
    case Endpoint_type::box:
        return Api::box_download_path;
    case Endpoint_type::s3:
        return Api::s3_download_path;
    case Endpoint_type::gftp:
        return Api::gftp_download_path;
    case Endpoint_type::http:
        return Api::http_download_path;
    }

    throw std::invalid_argument(Err::unknown_enum_msg);
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
    // recursively add contained resoruces
    std::vector<Resource> contained {};
    auto files {obj[Api::stat_files]};
    if (!files.error()) {
        for (const auto& r : files.value()) {
            // propogate up simdjson_error if thrown
            contained.push_back(create_resource(r.get_object().value()));
        }
    }

    auto id {obj[Api::stat_id]};
    auto link {obj[Api::stat_link]};
    auto permissions {obj[Api::stat_permissions]};

    // if simdjson_error is thrown, the dom must not meet the specification, so propogate the exception
    return {id.error() ? std::nullopt : std::optional {id.get_c_str().value()},
            obj[Api::stat_name].get_c_str().value(),
            obj[Api::stat_size].get_int64().value(),
            obj[Api::stat_time].get_int64().value(),
            obj[Api::stat_dir].get_bool().value(),
            obj[Api::stat_file].get_bool().value(),
            link.error() ? std::nullopt : std::optional {link.get_c_str().value()},
            permissions.error() ? std::nullopt : std::optional {permissions.get_c_str().value()},
            files.error() ? std::nullopt : std::optional {contained}};
}

/**
 * Creates a DeleteOperation json object with the specified fields.
 *
 * @param cred_id borrowed reference to the value of the corresponding json field
 * @param path borrowed reference to the value of the corresponding json field
 * @param id borrowed reference to the value of the corresponding json field
 * @param to_delete borrowed reference to the value of the corresponding json field
 *
 * @return the created json string corresponding to the DeleteOperation json object
 */
std::string create_delete_operation(const std::string& cred_id,
                                    const std::string& path,
                                    const std::string& id,
                                    const std::string& to_delete)
{
    std::ostringstream stream {};
    stream << "{\"" << Api::delete_operation_cred_id << "\":\"" << Util::escape_json(cred_id) << "\",\""
           << Api::delete_operation_path << "\":\"" << Util::escape_json(path) << "\",\"" << Api::delete_operation_id
           << "\":\"" << Util::escape_json(id) << "\",\"" << Api::delete_operation_to_delete << "\":\""
           << Util::escape_json(to_delete) << "\"}";

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
    stream << "{\"credId\":\"" << Util::escape_json(cred_id) << "\",\"path\":\"" << Util::escape_json(path)
           << "\",\"id\":\"" << Util::escape_json(id) << "\",\"folderToCreate\":\""
           << Util::escape_json(folder_to_create) << "\"}";

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
    stream << "{\"credId\":\"" << Util::escape_json(cred_id) << "\",\"path\":\"" << Util::escape_json(path)
           << "\",\"id\":\"" << Util::escape_json(id) << "\",\"fileToDownload\":\""
           << Util::escape_json(file_to_download) << "\"}";

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
      headers_ {Util::create_headers(ods_auth_token_)}
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
