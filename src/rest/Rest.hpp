/*
 * Rest.hpp
 * Andrew Mikalsen
 * 6/5/20
 */

#ifndef REST_HPP_INCLUDED
#define REST_HPP_INCLUDED

#include "Response.hpp"

namespace ods {
    namespace rest {
        /**
         * Class used to perform REST requests.
         */
        class Rest {
            public:
			    /**
				 * Performs a GET request to the specified url with the
				 * specified headers.
				 * 
				 * @param url borrowed reference to the string containing url to
				 * make the GET request to. Should ideally contain the protocol
				 * @param headers borrowed reference to the multi-map containing
				 * the headers for the GET request
				 * 
				 * @return Response object containing the response headers,
				 * body, and http status
				 */
				virtual Response get(const std::string& url, const std::unordered_multimap<std::string, std::string>& headers) const = 0;

                /**
				 * Performs a POST request to the specified url with the
				 * specified headers and data.
				 * 
				 * @param url borrowed reference to the string containing the
				 * url to make the POST request to, ideally containing the
				 * protocol
				 * @param headers borrowed reference to the multi-map containing
				 * the headers for the POST request
				 * @param data borrowed reference to the string containing the
				 * json data for the POST request
				 * 
				 * @return the Response object containing the response headers,
				 * body, and http status
				 */
				virtual Response post(const std::string& url, const std::unordered_multimap<std::string, std::string>& headers, const std::string& data) const = 0;

                Rest(const Rest&) = delete;
                Rest& operator=(const Rest&) = delete;

				virtual ~Rest() = 0;
			protected:
                Rest() = default;
        };
    }
}

#endif // REST_HPP_INCLUDED
