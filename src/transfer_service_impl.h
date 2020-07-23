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

class Destination_impl : public Destination {
public:
    Destination_impl(Endpoint_type type, const std::string& cred_id, const std::string& directory_identifier);

    virtual ~Destination_impl() = default;

    Destination_impl(const Destination_impl&) = default;
    Destination_impl& operator=(const Destination_impl&) = default;
    Destination_impl(Destination_impl&&) = default;
    Destination_impl& operator=(Destination_impl&&) = default;

private:
    const Endpoint_type type_;
    const std::string cred_id_;
    const std::string directory_identifier_;
};

class Source_impl : public Source {
public:
    Source_impl(Endpoint_type type,
                const std::string& cred_id,
                const std::string& directory_identifier,
                const std::vector<std::string>& resource_identifiers);

    virtual ~Source_impl() = default;

    Source_impl(const Source_impl&) = default;
    Source_impl& operator=(const Source_impl&) = default;
    Source_impl(Source_impl&&) = default;
    Source_impl& operator=(Source_impl&&) = default;

private:
    const Endpoint_type type_;
    const std::string cred_id_;
    const std::string directory_identifier_;
    const std::vector<std::string> resource_identifiers_;
};

class Transfer_options_impl : public Transfer_options {
public:
    Transfer_options_impl() = default;
    virtual ~Transfer_options_impl() = default;
};

class Transfer_status_impl : public Transfer_status {
    Transfer_status_impl() = default;
    virtual ~Transfer_status_impl() = default;
};

class Transfer_service_impl : public Transfer_service {
public:
    Transfer_service_impl(const std::string& ods_auth_token,
                          const std::string& ods_url,
                          std::unique_ptr<Rest> rest_caller);

    virtual ~Transfer_service_impl() = default;

    virtual std::string transfer(const Source& source,
                                 const Destination& destination,
                                 const Transfer_options& options) const override;

    virtual std::unique_ptr<Transfer_status> status(const std::string& id) const override;

private:
    const std::string ods_auth_token_;
    const std::string ods_url_;
    const std::unique_ptr<Rest> rest_caller_;
    const std::unordered_multimap<std::string, std::string> headers_;
};

} // namespace One_data_share

#endif // ONEDATASHARE_TRANSFER_SERVICE_IMPL_H