/*
 * Rest.hpp
 * Andrew Mikalsen
 * 6/5/20
 */

#ifndef REST_HPP_INCLUDED
#define REST_HPP_INCLUDED

#include "Response.hpp"

namespace ods {
    /**
     * Provides functions for making REST API calls.
     */
    namespace rest {
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
    }
}

#endif // REST_HPP_INCLUDED
