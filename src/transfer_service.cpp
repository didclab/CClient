/*
 * transfer_service.cpp
 * Andrew Mikalsen
 * 7/23/20
 */

#include <onedatashare/transfer_service.h>

namespace One_data_share {

std::unique_ptr<Destination> Destination::create(Endpoint_type type,
                                                 std::string cred_id,
                                                 std::string directory_identifier)
{
    // TODO: implement
    return nullptr;
}

Destination::Destination() = default;
Destination::~Destination() = default;

std::unique_ptr<Source> Source::create(Endpoint_type type,
                                       const std::string& cred_id,
                                       const std::string& directory_identifier,
                                       const std::vector<std::string>& resource_identifiers)
{
    // TODO: implement
    return nullptr;
}

Source::Source() = default;
Source::~Source() = default;

std::unique_ptr<Transfer_service> Transfer_service::create(const std::string& ods_auth_token)
{
    // TODO: implement
    return nullptr;
}

Transfer_service::Transfer_service() = default;
Transfer_service::~Transfer_service() = default;

} // namespace One_data_share