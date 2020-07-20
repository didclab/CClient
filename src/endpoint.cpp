/*
 * endpoint.cpp
 * Andrew Mikalsen
 * 7/20/20
 */

#include <onedatashare/endpoint.h>

namespace One_data_share {

    Resource::Resource() = default;

    Resource::~Resource() = default;

    std::unique_ptr<Endpoint> Endpoint::create(Endpoint_type type,
                                               const std::string& cred_id,
                                               const std::string& ods_auth_token)
    {
        // TODO: implement
        return nullptr;
    }

    Endpoint::Endpoint() = default;

    Endpoint::~Endpoint() = default;

}