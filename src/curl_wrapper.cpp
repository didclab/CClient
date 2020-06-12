/*
 * curl_wrapper.cpp
 * Andrew Mikalsen
 * 6/5/20
 */

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>
#include <curl/curl.h>
#include "../simdjson/simdjson.h"
#include "curl_wrapper.hpp"

namespace ods {
    namespace rest {
        namespace {
            /**
             * Sequence of newline characters.
             */
            const char* newline_chars("\n\r");

            /**
             * Used by libcurl to assign the response body from a request to the specified string.
             * 
             * @param buffer non-null-terminated char* received after making the request
             * @param size number that is always 1
             * @param nmemb size of the char* received
             * @param userp string that the char* buffer is written to
             */
            size_t write_data(void* buffer, size_t size, size_t nmemb, std::string& userp) {
                userp = std::string((char*) buffer, size * nmemb);
                return size * nmemb;
            }

            /**
             * Used by libcurl to add the response headers from a request to the specified string vector.
             * 
             * @param buffer non-null-terminated char* header received after making the request
             * @param size number that is always 1
             * @param nmemb size of the char* recieved
             * @param userp string vectors that the char* header is added to
             */
            size_t header_callback(void* buffer, size_t size, size_t nmemb, std::vector<std::string>& userp) {
                userp.push_back(std::string((char*) buffer, size * nmemb));
                return size * nmemb;
            }
        }

        /**
         * Converts the given vector of strings to a multimap by splitting each string at the specified delimiter and
         * skipping lines that don't contain the delimiter.
         * 
         * @param headers vector of strings to parse
         * @param delim delimiter used to split each string into (key, value) pairs
         * 
         * @return a multi-map containing each header from the input vector that contains the specified delimiter
         */
        const std::unordered_multimap<std::string, std::string> parse_headers(const std::vector<std::string>& headers, const std::string& delim) {
            std::unordered_multimap<std::string, std::string> map;
            int delim_len = delim.length();

            for (std::string h : headers) {
                // use the left side of delim as the key and the right side as the value
                int delim_start = h.find(delim);
                // skip string if it doesn't contain the delimiter
                if (delim_start != std::string::npos) {                    
                    // find where the string ends before newline characters
                    int h_end = h.find_last_not_of(newline_chars);
                    if (h_end == std::string::npos) {
                        h_end = h.length();
                    } else {
                        h_end += 1;
                    }
                    // insert the key,value pair
                    map.insert(std::pair<std::string, std::string>(h.substr(0, delim_start), h.substr(delim_start + delim_len, h_end - delim_start - delim_len)));
                }
             }

             return map;
        }

        /**
         * Uses the specified parser to convert the specified json string into a simdjson object.
         * 
         * @param json string to be converted into a simdjson object
         * @param parser parser used to parse the json string
         * 
         * @return an optional containing simdjson object with the data extracted from the json string if the string was
         * valid json, no value otherwise.
         */
        const std::optional<simdjson::dom::object> parse_json(const std::string& json, simdjson::dom::parser& parser) {
            auto [simd_obj, simd_err] = parser.parse(json).get<simdjson::dom::object>();
            if (!simd_err) {
                return simd_obj;
            } else {
                return {};
            }
        }

        const std::string Response::HEADER_DELIM = ": ";

        simdjson::dom::parser Response::PARSER;

        /**
         * Create a new Response object by parsing the inputs and converting them into their respective types.
         * 
		 * @param headers converted to an unordered map
		 * @param body converted to a simdjson object
		 * @param status converted to an integer
         */
        Response::Response(const std::vector<std::string> headers, const std::string body, const double status) :
            _headers(parse_headers(headers, HEADER_DELIM)),
            _body(parse_json(body, PARSER)),
            _status(status) {
        }

        const std::unordered_multimap<std::string, std::string>& Response::headers() const {
            return _headers;
        }

        const std::optional<simdjson::dom::object>& Response::body() const {
            return _body;
        }

        const int& Response::status() const {
            return _status;
        }

        /**
         * Initializes global data for libcurl.
         */
        void init() {
            curl_global_init(CURL_GLOBAL_ALL);
        }

        /**
         * Cleans global data for libcurl.
         */
        void cleanup() {
            curl_global_cleanup();
        }

        /**
         * Uses libcurl to perform a GET request to the specified url with the specified headers.
         * 
         * @param url string set as the url
         * @param headers vector of strings used to construct a curl string linked-list to set request headers
         * 
         * @return response body as a string generated by write_data
         */
        Response get(const std::string& url, const std::vector<std::string>& headers) {
            // string that curl will write the response body to
            std::string response_body;
            // string vector that curl will write the request headers to
            std::vector<std::string> response_headers;
            // long that the http response status will be written to
            long status;

            // initialize headers_slist, a linked-list of strings, which is used to specify the headers for the request
            curl_slist* headers_slist = nullptr;
            for (const std::string& h : headers) {
                headers_slist = curl_slist_append(headers_slist, h.c_str());
            }

            // execute the request
            CURL *handle = curl_easy_init();
            curl_easy_setopt(handle, CURLOPT_HTTPGET, 1L); // indicate a GET request
            curl_easy_setopt(handle, CURLOPT_URL, url.c_str()); // set url
            curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers_slist); // set headers

            curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data); // let body be written to a string
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, &response_body); // indicate the string to be written to
            curl_easy_setopt(handle, CURLOPT_HEADERFUNCTION, header_callback); // let headers be added to string vector
            curl_easy_setopt(handle, CURLOPT_HEADERDATA, &response_headers); // indicate the string vector

            const CURLcode result = curl_easy_perform(handle);

            curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &status); // set http status code to status

            // free resources
            curl_easy_cleanup(handle);
            curl_slist_free_all(headers_slist);

            return Response(response_headers, response_body, status);
        }

        // TODO: implement
        Response post(const std::string& url, const std::vector<std::string>& headers, const std::string& data);
    }
}
