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

/**
 * Class using libcurl to perform REST requests.
 */
class Curl_rest : public Rest {
public:
    /**
     * Creates a new Curl_rest object capable of making REST requests
     * via libcurl.
     */
    Curl_rest();

    Curl_rest(const Curl_rest&) = delete;

    Curl_rest& operator=(const Curl_rest&) = delete;

    Curl_rest(Curl_rest&&) = default;

    Curl_rest& operator=(Curl_rest&&) = default;

    virtual ~Curl_rest() override;

    virtual Response get(const std::string& url,
                         const std::unordered_multimap<std::string, std::string>& headers) const override;

    virtual Response post(const std::string& url,
                          const std::unordered_multimap<std::string, std::string>& headers,
                          const std::string& data) const override;
};

} // namespace One_data_share

#endif // ONEDATASHARE_CURL_REST_H