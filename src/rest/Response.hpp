/*
 * Response.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef RESPONSE_HPP_INCLUDED
#define RESPONSE_HPP_INCLUDED

#include <string>
#include <unordered_map>

namespace ods {
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
                Response(const std::unordered_multimap<std::string, std::string>& headers, const std::string& body, const int& status);

                Response(const Response&) = delete;
                Response& operator=(const Response&) = delete;

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
    }
}

#endif // RESPONSE_HPP_INCLUDED