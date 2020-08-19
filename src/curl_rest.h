/**
 * @file curl_rest.h
 * Defines a class wrapping libcurl used to make REST API calls.
 *
 * @author Andrew Mikalsen
 * @date 6/23/20
 */

#ifndef ONEDATASHARE_CURL_REST_H
#define ONEDATASHARE_CURL_REST_H

#include <string>
#include <unordered_map>

#include "rest.h"

namespace Onedatashare {
namespace Internal {

/**
 * Class using libcurl to perform REST requests.
 */
class Curl_rest : public Rest {
public:
    /**
     * Uses libcurl to perform a GET request to the specified url with the specified headers.
     *
     * @param url borrowed refrence to the string set as the url
     * @param headers borrowed refrence to the multi-map used to construct the request headers
     *
     * @return the Response object created from the values set by libcurl
     *
     * @exception Connection_error if unable to connect to the sepcified url
     */
    Response get(const std::string& url,
                 const std::unordered_multimap<std::string, std::string>& headers) const override;

    /**
     * Uses libcurl to perform a POST request to the specified url with the specified headers and data.
     *
     * @param url borrowed reference to the string set as the url
     * @param headers borrowed refrence to the multi-map used to construct the request headers

     * @param data borrowed reference to the json string passed in to libcurl to send as the POST data for the request
     *
     * @return the Response object created from the values set by libcurl
     *
     * @exception Connection_error if unable to connect to the sepcified url
     */
    Response post(const std::string& url,
                  const std::unordered_multimap<std::string, std::string>& headers,
                  const std::string& data) const override;
};

} // namespace Internal
} // namespace Onedatashare

#endif // ONEDATASHARE_CURL_REST_H
