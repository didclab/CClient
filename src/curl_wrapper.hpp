/*
 * curl_wrapper.hpp
 * Andrew Mikalsen
 * 6/5/20
 */

#ifndef CURL_WRAPPER_HPP_INCLUDED
#define CURL_WRAPPER_HPP_INCLUDED

#include <string>
#include <unordered_map>

namespace ods {
    /**
     * Provides functions for making REST API calls.
     */
    namespace rest {
        /**
         * Object holding the response from a request made via the get or post functions.
         * 
         * Fields of this object live only as long as the object itself.
         */
        class Response {
            public:
                /**
                 * Creates a new Response object.
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
                 * @return a json string containing the response body
                 */
                const std::string& body() const;
                /**
                 * Gets the http response status. This reference lives only as long as this object.
                 * 
                 * @return the http response status
                 */
                const int& status() const;
            private:
                /**
                 * Multi-map storing headers as (key, value) pairs.
                 */
                const std::unordered_multimap<std::string, std::string> _headers;
                /**
                 * Json string containing the response body.
                 */
                const std::string _body;
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
         * @param headers multi-map containing the headers for the GET request
         * 
         * @return Response object containing the response headers, body, and http status
         */
        Response get(const std::string& url, const std::unordered_multimap<std::string, std::string>& headers);

        /**
         * Performs a POST request to the specified url with the specified headers and data.
         * 
         * @param url string containing the url to make the POST request to. Should ideally contain the protocol
         * @param headers multi-map containing the headers for the POST request
         * @param data string containing the json data for the POST request
         * 
         * @return Response object containing the response headers, body, and http status
         */
        Response post(const std::string& url, const std::unordered_multimap<std::string, std::string>& headers, const std::string& data);
    }
}

#endif // CURL_WRAPPER_HPP_INCLUDED