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
}

#endif // ONEDATASHARE_UTILS_H