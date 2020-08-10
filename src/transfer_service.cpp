/**
 * @file transfer_service.cpp
 *
 * @author Andrew Mikalsen
 * @date 7/23/20
 */

#include <onedatashare/transfer_service.h>

#include "curl_rest.h"
#include "transfer_service_impl.h"
#include "utils.h"

namespace One_data_share {

std::unique_ptr<Transfer_service> Transfer_service::create(const std::string& ods_auth_token)
{
    return create(ods_auth_token, Internal::ods_production_url);
}

std::unique_ptr<Transfer_service> Transfer_service::create(const std::string& ods_auth_token, const std::string& url)
{
    return std::make_unique<Internal::Transfer_service_impl>(ods_auth_token,
                                                             url,
                                                             std::make_unique<Internal::Curl_rest>());
}

Transfer_service::Transfer_service() = default;
Transfer_service::~Transfer_service() = default;

} // namespace One_data_share
