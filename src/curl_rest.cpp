/*
 * curl_rest.cpp
 * Andrew Mikalsen
 * 6/23/20
 */

#include <optional>
#include <utility>

#include <curl/curl.h>

#include <onedatashare/ods_error.h>

#include "curl_rest.h"

namespace {
    /**
     * Sequence of newline characters.
     */
    constexpr auto newline_chars {"\n\r"};

    /**
     * String separating keys from values when parsing headers.
     */
    constexpr auto header_delim {": "};

    /**
     * Converts the specified string into a (key, value) pair if the string contains the specified delimiter by
     * splitting it at the delimiter.
     *
     * @param header borrowed reference to the string to convert to a pair
     * @param delim borrowed reference to the string determining which part of the header is the key and which part is
     * the value
     *
     * @return a pair if the string contains the specified delimiter, no value otherwise
     */
    const std::optional<std::pair<std::string, std::string>> parse_header(const std::string& header,
                                                                          const std::string& delim)
    {
        auto del_len {delim.length()};
        auto del_start {header.find(delim)};
        if (del_start != std::string::npos) {
            // find where the header ends (i.e. the last index before any newline characters)
            auto h_end {header.find_last_not_of(newline_chars)};
            if (h_end == std::string::npos) {
                // no newline characters so the length is the length
                h_end = header.length();
            } else {
                h_end += 1;
            }
            // use the left side of the delim as the key and the right side as the vlaue for the key, value pair
            return std::pair<std::string, std::string> {
                header.substr(0, del_start),
                header.substr(del_start + del_len, h_end - del_start - del_len)};
        } else {
            // if the header doesnt contain the delimiter return no value
            return {};
        }
    }

    /**
     * Used by libcurl to assign the response body from a request to the specified string.
     *
     * @param buffer non-null-terminated char* received after making the request
     * @param size number that is always 1
     * @param nmemb size of the char* received
     * @param userp string that the char* buffer is written to
     */
    size_t write_data(void* buffer, size_t size, size_t nmemb, std::string& userp)
    {
        userp = std::string {(char*) buffer, size * nmemb};
        return size * nmemb;
    }

    /**
     * Used by libcurl to add the response headers from a request to the specified multi-map.
     *
     * @param buffer non-null-terminated char* header received after making the request
     * @param size number that is always 1
     * @param nmemb size of the char* recieved
     * @param userp multi-map that the (key, value) pair extracted from the header is added to
     */
    size_t header_callback(void* buffer,
                           size_t size,
                           size_t nmemb,
                           std::unordered_multimap<std::string, std::string>& userp)
    {
        auto header {parse_header(std::string {(char*) buffer, size * nmemb}, header_delim)};
        if (header) {
            // if the header containd the delimiter add the corresponding pair to the map
            userp.insert(header.value());
        }
        return size * nmemb;
    }
}

namespace One_data_share {
    /**
     * Initializes the global data needed for libcurl.
     */
    Curl_rest::Curl_rest()
    {
        curl_global_init(CURL_GLOBAL_ALL);
    }

    /**
     * Cleans up the global data needed for libcurl.
     */
    Curl_rest::~Curl_rest()
    {
        curl_global_cleanup();
    }

    /**
     * Uses libcurl to perform a GET request to the specified url with the specified headers.
     *
     * @param url borrowed refrence to the string set as the url
     * @param headers borrowed refrence to the multi-map used to construct a curl string linked-list to set request
     * headers
     *
     * @return the Response object created by the write_data and header_callback functions
     *
     * @exception Connection_error if unable to connect to the sepcified url
     */
    Response Curl_rest::get(const std::string& url,
                            const std::unordered_multimap<std::string, std::string>& headers) const
    {
        // string that curl will write the response body to
        std::string response_body {};

        // multi-map that curl will write the request headers to
        std::unordered_multimap<std::string, std::string> response_headers {};

        // long that the http response status will be written to
        long status;

        // initialize headers_slist, a linked-list of strings, which is used to specify the headers for the request
        curl_slist* headers_slist {nullptr};
        for (auto h : headers) {
            headers_slist = curl_slist_append(headers_slist, (h.first + header_delim + h.second).c_str());
        }

        // execute the request
        CURL* handle {curl_easy_init()};
        curl_easy_setopt(handle, CURLOPT_HTTPGET, 1L);
        curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
        curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers_slist);

        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, &response_body);
        curl_easy_setopt(handle, CURLOPT_HEADERFUNCTION, header_callback);
        curl_easy_setopt(handle, CURLOPT_HEADERDATA, &response_headers);

        const CURLcode result {curl_easy_perform(handle)};

        curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &status);

        // free resources
        curl_easy_cleanup(handle);
        curl_slist_free_all(headers_slist);

        if (result != CURLE_OK) {
            throw Connection_error {"Unable to connect to " + url + ": " + curl_easy_strerror(result)};
        }

        return Response {response_headers, response_body, (int) status};
    }

    /**
     * Uses libcurl to perform a POST request to the specified url with the specified headers and data.
     *
     * @param url borrowed reference to the string set as the url
     * @param headers borrowed reference to the multi-map used to construct a curl string linked-list to set request
     * headers
     * @param data borrowed reference to the json string passed in to libcurl to send as the POST data for the request
     *
     * @return the Response object created by the write_data and header_callback functions
     *
     * @exception Connection_error if unable to connect to the sepcified url
     */
    Response Curl_rest::post(const std::string& url,
                             const std::unordered_multimap<std::string, std::string>& headers,
                             const std::string& data) const
    {
        // string that curl will write the response body to
        std::string response_body {};

        // multi-map that curl will write the request headers to
        std::unordered_multimap<std::string, std::string> response_headers {};

        // long that the http response status will be written to
        long status;

        // initialize headers_slist, a linked-list of strings, which is used to specify the headers for the request
        curl_slist* headers_slist {nullptr};
        for (auto h : headers) {
            headers_slist = curl_slist_append(headers_slist, (h.first + header_delim + h.second).c_str());
        }

        // execute the request
        CURL* handle {curl_easy_init()};
        curl_easy_setopt(handle, CURLOPT_URL, url.c_str());
        curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers_slist);

        curl_easy_setopt(handle, CURLOPT_POSTFIELDS, data.c_str());

        curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(handle, CURLOPT_WRITEDATA, &response_body);
        curl_easy_setopt(handle, CURLOPT_HEADERFUNCTION, header_callback);
        curl_easy_setopt(handle, CURLOPT_HEADERDATA, &response_headers);

        const CURLcode result {curl_easy_perform(handle)};

        curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &status);

        // free resources
        curl_easy_cleanup(handle);
        curl_slist_free_all(headers_slist);

        if (result != CURLE_OK) {
            throw Connection_error {"Unable to connect to " + url + ": " + curl_easy_strerror(result)};
        }

        return Response {response_headers, response_body, (int) status};
    }
}