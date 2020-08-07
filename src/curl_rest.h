/*
 * curl_rest.h
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef ONEDATASHARE_CURL_REST_H
#define ONEDATASHARE_CURL_REST_H

#include <string>
#include <unordered_map>

#include "rest.h"

namespace One_data_share {

namespace Internal {

/**
 * Class using libcurl to perform REST requests.
 */
class Curl_rest : public Rest {
public:
    Curl_rest() = default;

    Response get(const std::string& url,
                 const std::unordered_multimap<std::string, std::string>& headers) const override;

    Response post(const std::string& url,
                  const std::unordered_multimap<std::string, std::string>& headers,
                  const std::string& data) const override;
};

} // namespace Internal

} // namespace One_data_share

#endif // ONEDATASHARE_CURL_REST_H