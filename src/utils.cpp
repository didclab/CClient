/**
 * @file utils.cpp
 *
 * @author Andrew Mikalsen
 * @date 7/21/20
 */

#include <fstream>
#include <iomanip>
#include <sstream>
#include <utility>

#include "utils.h"

namespace One_data_share {
namespace Internal {

namespace {

/** Content type header. */
constexpr auto header_content_type {"Content-Type"};

/** Value of content type header. */
constexpr auto header_json {"application/json"};

/** Authorization header. */
constexpr auto header_authorization {"Authorization"};

/** Part of the value of authorization header. */
constexpr auto header_bearer {"Bearer "};

/** Path from project root to file containing configured ods url. */
constexpr auto url_config_file_location {"url.txt"};

} // namespace

std::unordered_multimap<std::string, std::string> create_headers(const std::string& ods_auth_token)
{
    return std::unordered_multimap<std::string, std::string> {
        std::pair<std::string, std::string> {header_content_type, header_json},
        std::pair<std::string, std::string> {header_authorization, header_bearer + ods_auth_token}};
}

std::string as_string(Endpoint_type type)
{
    switch (type) {
    case Endpoint_type::box:
        return "box";
    case Endpoint_type::dropbox:
        return "dropbox";
    case Endpoint_type::ftp:
        return "ftp";
    case Endpoint_type::gftp:
        return "gftp";
    case Endpoint_type::google_drive:
        return "gdrive";
    case Endpoint_type::http:
        return "http";
    case Endpoint_type::s3:
        return "s3";
    case Endpoint_type::sftp:
        return "sftp";
    default:
        // TODO: throw exception
        return "";
    }
}

std::string escape_json(const std::string& json)
{
    // see also:
    // https://stackoverflow.com/questions/7724448/simple-json-string-escape-for-c/33799784#33799784
    std::ostringstream stream {};
    for (auto c : json) {
        switch (c) {
        case '"':
            stream << "\\\"";
            break;
        case '\\':
            stream << "\\\\";
            break;
        case '\b':
            stream << "\\b";
            break;
        case '\f':
            stream << "\\f";
            break;
        case '\n':
            stream << "\\n";
            break;
        case '\r':
            stream << "\\r";
            break;
        case '\t':
            stream << "\\t";
            break;
        default:
            if ('\x00' <= c && c <= '\x1f') {
                stream << "\\u" << std::setfill('0') << (int) c;
            } else {
                stream << c;
            }
        }
    }
    return stream.str();
}

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

} // namespace Internal
} // namespace One_data_share
