/*
 * curl_wrapper.hpp
 * Andrew Mikalsen
 * 6/5/20
 */

#ifndef CURL_WRAPPER_HPP_INCLUDED
#define CURL_WRAPPER_HPP_INCLUDED

#include <optional>
#include <string>
#include <unordered_map>
#include "../simdjson/simdjson.h"

namespace ods {
    /**
     * Provides functions for REST API calls that send and recieve JSON data. Is not thread safe.
     */
    namespace rest {
        /**
         * Object holding the response from a request made via the get or post functions.
         * 
         * This object should be used to extract the needed values and then discarded immediately. Fields of this object
         * live only as long as the object itself. It is not safe to instantiate instances of this object in different
         * threads.
         */
        class Response {
            public:
                /**
                 * Creates a new Response object.
                 * 
                 * It is not safe to use this constructor to create Response objects on separate threads.
                 * 
                 * @param headers multi-map containing the response headers
                 * @param body json string containing the response body
                 * @param status integer corresponding to the http response status
                 */
                Response(const std::unordered_multimap<std::string, std::string> headers, const std::string body, const int status);

                /**
                 * Gets the response headers. This reference lives only as long as this object.
                 * 
                 * @return the response headers stored as (key, value) pairs in an unordered multi-map
                 */
                const std::unordered_multimap<std::string, std::string>& headers() const;
                /**
                 * Gets the response body. This reference lives only as long as this object.
                 * 
                 * @return an optional containing a simdjson object if the response body was valid json, no value otherwise.
                 */
                const std::optional<simdjson::dom::object>& body() const;
                /**
                 * Gets the http response status. This reference lives only as long as this object.
                 * 
                 * @return the http response status
                 */
                const int& status() const;
            private:
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
                const std::optional<simdjson::dom::object> _body;
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
         * Performs a GET request to the specified url with the specified headers. Is not thread safe.
         * 
         * @param url string containing url to make the GET request to. Should ideally contain the protocol
         * @param headers multi-map containing the headers for the GET request
         * 
         * @return Response object containing the response headers, body, and http status
         */
        Response get(const std::string& url, const std::unordered_multimap<std::string, std::string>& headers);
        Response post(const std::string& url, const std::unordered_multimap<std::string, std::string>& headers, const std::string& data);
    }
}

#endif // CURL_WRAPPER_HPP_INCLUDED