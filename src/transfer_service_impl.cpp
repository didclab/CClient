/*
 * transfer_service_impl.cpp
 * Andrew Mikalsen
 * 7/23/20
 */

#include <sstream>
#include <utility>

#include "transfer_service_impl.h"
#include "utils.h"

namespace One_data_share {

namespace {

/**
 * Creates an EntityInfo json object with the specified fields
 *
 * @param id borrowed reference to the id to use for the EntityInfo
 * @param path borrowed reference to the path to use for the EntityInfo
 * @param size the size to use for the EntityInfo
 *
 * @return json string generated
 */
std::string create_entity_info(const std::string& id, const std::string& path, int size)
{
    // TODO: implement
    return "";
}

/**
 * Creates a Source json object from the specified Source object.
 *
 * @param source the Source object to generate json from
 *
 * @return json string generated
 */
std::string create_source(const Source& source)
{
    std::ostringstream stream {};

    // TODO: implement
    return "";
}

/**
 * Creates a Destination json object from the specified Destination object.
 *
 * @param destination the Destination object to generate json from
 *
 * @return json string generated
 */
std::string create_destination(const Destination& destination)
{
    // TODO: implement
    return "";
}

/**
 * Creates a TransferOptions json object from the specified Transfer_options object.
 *
 * @param options the Transfer_options object to generate json from
 *
 * @return json string generated
 */
std::string create_transfer_options(const Transfer_options& options)
{
    // TODO: implement
    return "";
}

/**
 * Creates a TransferJobRequest json object from the specified Source, Destination, and Transfer_options objects.
 *
 * @param source the Source object to generate json from
 * @param destination the Destination object to generate json from
 * @param options the Transfer_options object to generate json from
 *
 * @return json string generated
 */
std::string create_transfer_job_request(const Source& source,
                                        const Destination& destination,
                                        const Transfer_options& options)
{
    // TODO: implement
    return "";
}

} // namespace

Transfer_service_impl::Transfer_service_impl(const std::string& ods_auth_token,
                                             const std::string& ods_url,
                                             std::unique_ptr<Rest> rest_caller)
    : ods_auth_token_(ods_auth_token),
      ods_url_(ods_url),
      rest_caller_(std::move(rest_caller)),
      headers_(create_headers(ods_auth_token_))
{}

std::string Transfer_service_impl::transfer(const Source& source,
                                            const Destination& destination,
                                            const Transfer_options& options) const
{
    // TODO: impl
    return "";
}

std::unique_ptr<Transfer_status> Transfer_service_impl::status(const std::string& id) const
{
    // TODO: impl
    return nullptr;
}

} // namespace One_data_share