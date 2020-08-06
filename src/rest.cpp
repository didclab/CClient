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
    : headers {headers},
      body {body},
      status {status}
{}

Rest::Rest() = default;

Rest::~Rest() = default;

} // namespace Internal

} // namespace One_data_share
