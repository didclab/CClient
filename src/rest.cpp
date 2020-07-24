/*
 * rest.cpp
 * Andrew Mikalsen
 * 6/5/20
 */

#include "rest.h"

namespace One_data_share {

namespace Internal {

Response::Response(const std::unordered_multimap<std::string, std::string>& headers,
                   const std::string& body,
                   int status)
    : headers_ {headers},
      body_ {body},
      status_ {status}
{}

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

Rest::Rest() = default;

Rest::~Rest() = default;

} // namespace Internal

} // namespace One_data_share
