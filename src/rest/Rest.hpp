/*
 * Rest.hpp
 * Andrew Mikalsen
 * 6/5/20
 */

#ifndef REST_HPP_INCLUDED
#define REST_HPP_INCLUDED

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

        /**
         * Class used to perform REST requests.
         */
        class Rest {
            public:
                Rest() = default;
                Rest(const Rest&) = delete;
                Rest& operator=(const Rest&) = delete;
			    /**
				 * Performs a GET request to the specified url with the specified headers.
				 * 
				 * @param url string containing url to make the GET request to. Should ideally contain the protocol
				 * @param headers multi-map containing the headers for the GET request
				 * 
				 * @return Response object containing the response headers, body, and http status
				 */
				virtual Response get(const std::string& url, const std::unordered_multimap<std::string, std::string>& headers) const = 0;
                /**
				 * Performs a POST request to the specified url with the specified headers and data.
				 * 
				 * @param url string containing the url to make the POST request to. Should ideally contain the protocol
				 * @param headers multi-map containing the headers for the POST request
				 * @param data string containing the json data for the POST request
				 * 
				 * @return Response object containing the response headers, body, and http status
				 */
				virtual Response post(const std::string& url, const std::unordered_multimap<std::string, std::string>& headers, const std::string& data) const = 0;
				virtual ~Rest() = 0;
        };

        /**
         * Class using libcurl to perform REST requests.
         */
        class CurlRest : public Rest {
            public:
                /**
                 * Creates a new CurlRest object capable of making REST requests via libcurl.
                 */
                CurlRest();
                virtual Response get(const std::string& url, const std::unordered_multimap<std::string, std::string>& headers) const override;
                virtual Response post(const std::string& url, const std::unordered_multimap<std::string, std::string>& headers, const std::string& data) const override;
                virtual ~CurlRest() override;
        };
    }
}

#endif // REST_HPP_INCLUDED
