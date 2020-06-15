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
             * String separating keys from values when parsing headers.
             */
            const std::string header_delim(": ");
            
            /**
             * Converts the specified string into a (key, value) pair if the string contains the specified delimiter by
             * splitting it at the delimiter.
             * 
             * @param header string to convert to a pair
             * @param delim string determining which part of the header is the key and which part is the value
             * 
             * @return a pair if the string contains the specified delimiter, no value otherwise
             */
            const std::optional<std::pair<std::string, std::string>> parse_header(const std::string& header, const std::string& delim) {
				int del_len = delim.length();
				int del_start = header.find(delim);
				if (del_start != std::string::npos) {
					// find where the header ends (i.e. the last index before any newline characters)
					int h_end = header.find_last_not_of(newline_chars);
					if (h_end == std::string::npos) {
						// no newline characters so the length is the length
						h_end = header.length();
					} else {
						h_end += 1;
					}
					// use the left side of the delim as the key and the right side as the vlaue for the key, value pair
					return std::pair<std::string, std::string>(header.substr(0, del_start), header.substr(del_start + del_len, h_end - del_start - del_len));
				} else {
					// if the header doesnt contain the delimiter return no value
					return {};
				}
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
             * Used by libcurl to add the response headers from a request to the specified multi-map.
             * 
             * @param buffer non-null-terminated char* header received after making the request
             * @param size number that is always 1
             * @param nmemb size of the char* recieved
             * @param userp multi-map that the (key, value) pair extracted from the header is added to
             */
            size_t header_callback(void* buffer, size_t size, size_t nmemb, std::unordered_multimap<std::string, std::string>& userp) {
                auto header = parse_header(std::string((char*) buffer, size * nmemb), header_delim);
                if (header) {
                    // if the header containd the delimiter add the corresponding pair to the map
                    userp.insert(header.value());
                }
                return size * nmemb;
            }
        }

        simdjson::dom::parser Response::PARSER;

        Response::Response(const std::unordered_multimap<std::string, std::string> headers, const std::string body, const int status) :
            _headers(headers),
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
         * @param headers multi-map used to construct a curl string linked-list to set request headers
         * 
         * @return response body as a string generated by write_data
         */
        Response get(const std::string& url, const std::unordered_multimap<std::string, std::string>& headers) {
            // string that curl will write the response body to
            std::string response_body;
            // multi-map that curl will write the request headers to
            std::unordered_multimap<std::string, std::string> response_headers;
            // long that the http response status will be written to
            long status;

            // initialize headers_slist, a linked-list of strings, which is used to specify the headers for the request
            curl_slist* headers_slist = nullptr;
            for (const std::pair<std::string, std::string>& h : headers) {
                headers_slist = curl_slist_append(headers_slist, (h.first + header_delim + h.second).c_str());
            }

            // execute the request
            CURL *handle = curl_easy_init();
            curl_easy_setopt(handle, CURLOPT_HTTPGET, 1L); // indicate a GET request
            curl_easy_setopt(handle, CURLOPT_URL, url.c_str()); // set url
            curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers_slist); // set headers

            curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_data); // let body be written to a string
            curl_easy_setopt(handle, CURLOPT_WRITEDATA, &response_body); // indicate the string to be written to
            curl_easy_setopt(handle, CURLOPT_HEADERFUNCTION, header_callback); // let headers be added to map
            curl_easy_setopt(handle, CURLOPT_HEADERDATA, &response_headers); // indicate the map

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
