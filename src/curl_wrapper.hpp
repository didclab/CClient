/*
 * curl_wrapper.hpp
 * Andrew Mikalsen
 * 6/5/20
 */

#ifndef CURL_WRAPPER_HPP_INCLUDED
#define CURL_WRAPPER_HPP_INCLUDED

#include <string>

namespace ods {
    namespace curl {
        /**
         * Performs a GET request to the specified url with the specified headers.
         * 
         * @arg url string containing url to make the GET request to. Should ideally contain the protocol
         * @arg headers vector of strings used as headers for the GET request
         * 
         * @return response from the request
         */
        std::string get(const std::string& url, const std::vector<std::string>& headers);
        std::string post(const std::string& url, const std::vector<std::string>& headers, const std::string& data);
    }
}

#endif // CURL_WRAPPER_HPP_INCLUDED