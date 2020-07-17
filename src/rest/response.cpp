/*
 * response.cpp
 * Andrew Mikalsen
 * 6/23/20
 */

#include "response.h"

namespace One_data_share {
    Response::Response(std::unordered_multimap<std::string, std::string> headers, std::string body, int status)
        : headers_{headers}, body_{body}, status_{status} {}

    const std::unordered_multimap<std::string, std::string>& Response::headers() const
    {
        return headers_;
    }

    const std::string& Response::body() const
    {
        return body_;
    }

    int Response::status() const
    {
        return status_;
    }
}