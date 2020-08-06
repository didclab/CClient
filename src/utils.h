/*
 * utils.h
 * Andrew Mikalsen
 * 7/21/20
 */

#ifndef ONEDATASHARE_UTILS_H
#define ONEDATASHARE_UTILS_H

#include <string>
#include <unordered_map>

#include <onedatashare/endpoint_type.h>

namespace One_data_share {

namespace Internal {

/** Production url for One Data Share. */
static constexpr auto ods_production_url {"https://onedatashare.org"};

/**
 * Creates the required header map using the specified token.
 *
 * @param ods_auth_token token used to create the headers
 *
 * @return map of the headers needed to make REST API calls
 */
std::unordered_multimap<std::string, std::string> create_headers(const std::string& ods_auth_token);

/**
 * Converts an endpoint type to the string needed for the REST API.
 *
 * @param type endpoint type to convert
 *
 * @return endpoint type as a string understood by the REST API
 */
std::string endpoint_as_string(const Endpoint_type type);

/**
 * Escapes characters in the given json string.
 *
 * @param json borrowed reference to the json string to escape
 *
 * @return a copy of the json string with its characters escaped
 */
std::string escape_json(const std::string& json);

/**
 * Sets the url in the config file to the specified string.
 *
 * @param url mutably borrowed reference to the string to set the read url to
 *
 * @return true if and only if the config file was found and could be opened
 */
bool load_url_from_config(std::string& url);

} // namespace Internal

} // namespace One_data_share

#endif // ONEDATASHARE_UTILS_H