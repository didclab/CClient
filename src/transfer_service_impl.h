/*
 * transfer_service_impl.h
 * Andrew Mikalsen
 * 7/23/20
 */

#ifndef ONEDATASHARE_TRANSFER_SERVICE_IMPL_H
#define ONEDATASHARE_TRANSFER_SERVICE_IMPL_H

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <onedatashare/endpoint_type.h>
#include <onedatashare/transfer_service.h>

#include "rest.h"

namespace One_data_share {

namespace Internal {

class Transfer_status_impl : public Transfer_status {
    Transfer_status_impl() = default;
    virtual ~Transfer_status_impl() = default;
};

class Transfer_service_impl : public Transfer_service {
public:
    Transfer_service_impl(const std::string& ods_auth_token,
                          const std::string& ods_url,
                          std::unique_ptr<Rest> rest_caller);

    ~Transfer_service_impl() override = default;

    std::string transfer(const Source& source,
                                 const Destination& destination,
                                 const Transfer_options& options) const override;

    std::unique_ptr<Transfer_status> status(const std::string& id) const override;

private:
    const std::string ods_auth_token_;
    const std::string ods_url_;
    const std::unique_ptr<Rest> rest_caller_;
    const std::unordered_multimap<std::string, std::string> headers_;
};

} // namespace Internal

} // namespace One_data_share

#endif // ONEDATASHARE_TRANSFER_SERVICE_IMPL_H