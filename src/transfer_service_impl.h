/*
 * transfer_service_impl.h
 * Andrew Mikalsen
 * 7/23/20
 */

#ifndef ONEDATASHARE_TRANSFER_SERVICE_IMPL_H
#define ONEDATASHARE_TRANSFER_SERVICE_IMPL_H

#include <string>
#include <vector>

#include <onedatashare/endpoint_type.h>
#include <onedatashare/transfer_service.h>

namespace One_data_share {

class Destination_impl : public Destination {
public:
    Destination_impl(Endpoint_type type, std::string cred_id, std::string directory_identifier);

    ~Destination_impl() = default;

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

    ~Source_impl() = default;

    Source_impl(const Source_impl&) = default;
    Source_impl& operator=(const Source_impl&) = default;
    Source_impl(Source_impl&&) = default;
    Source_impl& operator=(Source_impl&&) = default;

private:
};

class Transfer_service_impl : public Transfer_service {
public:
private:
};

} // namespace One_data_share

#endif // ONEDATASHARE_TRANSFER_SERVICE_IMPL_H