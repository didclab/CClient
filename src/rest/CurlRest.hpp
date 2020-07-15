/*
 * CurlRest.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef CURL_REST_HPP_INCLUDED
#define CURL_REST_HPP_INCLUDED

#include "Rest.hpp"

namespace ods {
    namespace rest {
        /**
         * Class using libcurl to perform REST requests.
         */
        class CurlRest : public Rest {
            public:
                /**
                 * Creates a new CurlRest object capable of making REST requests
                 * via libcurl.
                 */
                CurlRest();
                virtual Response get(const std::string& url, const std::unordered_multimap<std::string, std::string>& headers) const override;
                virtual Response post(const std::string& url, const std::unordered_multimap<std::string, std::string>& headers, const std::string& data) const override;
                virtual ~CurlRest() override;
        };
    }
}

#endif // CURL_REST_HPP_INCLUDED