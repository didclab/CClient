/**
 * @file transfer_service_impl.cpp
 *
 * @author Andrew Mikalsen
 * @date 7/23/20
 */

#include <sstream>
#include <utility>

#include <onedatashare/ods_error.h>

#include "error_message.h"
#include "ods_rest_api.h"
#include "transfer_service_impl.h"
#include "util.h"

namespace Onedatashare {
namespace Internal {

namespace {

/**
 * Creates an EntityInfo json object with the specified fields
 *
 * @param id borrowed reference to the id to use for the EntityInfo
 * @param path borrowed reference to the path to use for the EntityInfo
 *
 * @return json string generated
 */
std::string create_entity_info(const std::string& id, const std::string& path)
{
    std::ostringstream stream {};
    stream << "{\"" << Api::entity_info_id << "\":\"" << Util::escape_json(id) << "\",\"" << Api::entity_info_path
           << "\":\"" << Util::escape_json(path) << "\"}";

    return stream.str();
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
    stream << "{\"" << Api::source_type << "\":\"" << Util::as_string(source.type) << "\",\"" << Api::source_cred_id
           << "\":\"" << Util::escape_json(source.cred_id) << "\",\"" << Api::source_info
           << "\":" << create_entity_info(source.directory_identifier, source.directory_identifier) << ",\""
           << Api::source_info_list << "\":[";

    // create json array of EntityInfo json objects
    auto first {true};
    for (const auto& id : source.resource_identifiers) {
        // print comma prefix for each element other than the first
        if (!first) {
            stream << ",";
        } else {
            first = false;
        }
        stream << create_entity_info(id, id);
    }
    stream << "]}";

    return stream.str();
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
    std::ostringstream stream {};
    stream << "{\"" << Api::destination_type << "\":\"" << Util::as_string(destination.type) << "\",\""
           << Api::destination_cred_id << "\":\"" << Util::escape_json(destination.cred_id) << "\",\""
           << Api::destination_info
           << "\":" << create_entity_info(destination.directory_identifier, destination.directory_identifier) << "}";

    return stream.str();
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
    std::ostringstream stream;
    stream << "{\"" << Api::transfer_job_request_source << "\":" << create_source(source) << ", \""
           << Api::transfer_job_request_destination << "\":" << create_destination(destination) << "}";

    return stream.str();
}

} // namespace

Transfer_service_impl::Transfer_service_impl(const std::string& ods_auth_token,
                                             const std::string& ods_url,
                                             std::unique_ptr<Rest> rest_caller)
    : ods_url_(ods_url),
      rest_caller_(std::move(rest_caller)),
      headers_(Util::create_headers(ods_auth_token))
{}

std::string Transfer_service_impl::transfer(const Source& source,
                                            const Destination& destination,
                                            const Transfer_options& options) const
{
    // if post throws an exception, propogate it up
    const auto response {rest_caller_->post(ods_url_ + Api::transfer_job_path,
                                            headers_,
                                            create_transfer_job_request(source, destination, options))};

    if (response.status != 200) {
        // expected status 200
        throw Unexpected_response_error {Err::expect_200_msg, response.status};
    }

    return response.body;
}

std::unique_ptr<Transfer_status> Transfer_service_impl::status(const std::string& id) const
{
    // TODO: impl
    return nullptr;
}

} // namespace Internal
} // namespace Onedatashare
