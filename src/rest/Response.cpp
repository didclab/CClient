/*
 * Response.cpp
 * Andrew Mikalsen
 * 6/23/20
 */

#include "Response.hpp"

namespace ods {
    namespace rest {
        Response::Response(const std::unordered_multimap<std::string, std::string>& headers, const std::string& body, const int& status) :
            _headers(headers),
            _body(body),
            _status(status) {
        }

        const std::unordered_multimap<std::string, std::string>& Response::headers() const {
            return _headers;
        }

        const std::string& Response::body() const {
            return _body;
        }

        const int& Response::status() const {
            return _status;
        }
    }
}