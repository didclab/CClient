/*
 * curl_wrapper.hpp
 * Andrew Mikalsen
 * 6/5/20
 */

#ifndef CURL_WRAPPER_HPP_INCLUDED
#define CURL_WRAPPER_HPP_INCLUDED

#include <unordered_map>
#include <string>
#include "../simdjson/simdjson.h"

namespace ods {
    /**
     * Provides functions for REST API calls that send and recieve JSON data.
     */
    namespace rest {
        /**
         * Object holding the response from a request made via the get or post functions.
         */
        class Response {
            public:
                // TODO: decide how to handle body not being json

                /**
                 * Creates a new Response object.
                 * 
                 * @param headers vector of strings containing the response headers
                 * @param body json string containing the response body
                 * @param status double corresponding to the http response status
                 */
                Response(const std::vector<std::string> headers, const std::string body, const double status);

                /**
                 * Gets the response headers.
                 * 
                 * @return the response headers stored as (key, value) pairs in an unordered multi-map
                 */
                const std::unordered_multimap<std::string, std::string>& headers() const;
                /**
                 * Gets the response body.
                 * 
                 * @return a simdjson object which maps each field in the json string to its value
                 */
                const simdjson::dom::object& body() const;
                /**
                 * Gets the http response status.
                 * 
                 * @return the http response status
                 */
                const int& status() const;
            private:
                /**
                 * String separating keys from values when parsing headers.
                 */
                static const std::string HEADER_DELIM;
                /**
                 * Parses json strings.
                 */
                static simdjson::dom::parser PARSER;
                /**
                 * Stores headers as (key, value) pairs.
                 */
                const std::unordered_multimap<std::string, std::string> _headers;
                /**
                 * Stores the json response body.
                 */
                const simdjson::dom::object _body;
                /**
                 * The http response status code.
                 */
                const int _status;
        };

        /**
         * Initializes global data. Must be the first function called from the rest namespace. Is not thread safe.
         */
        void init();

        /**
         * Cleans up global data. Must be the last function called from the rest namespace. Is not thread safe.
         */
        void cleanup();

        /**
         * Performs a GET request to the specified url with the specified headers.
         * 
         * @param url string containing url to make the GET request to. Should ideally contain the protocol
         * @param headers vector of strings used as headers for the GET request
         * 
         * @return Response object containing the response headers, body, and http status
         */
        Response get(const std::string& url, const std::vector<std::string>& headers);
        Response post(const std::string& url, const std::vector<std::string>& headers, const std::string& data);
    }
}

#endif // CURL_WRAPPER_HPP_INCLUDED