/**
 * @file transfer_service_impl.h
 * Defines the internal implementation for classes needed to make and observe transfer requests.
 *
 * @author Andrew Mikalsen
 * @name 7/23/20
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

/**
 * Indicates the status of a transfer.
 */
class Transfer_status_impl : public Transfer_status {
};

/**
 * Service that makes REST API calls to One Data Share related to transfers.
 */
class Transfer_service_impl : public Transfer_service {
public:
    /**
     * Creates a new Transfer_service object with the specified connection to One Data Share and rest caller.
     *
     * @param ods_auth_token borrowed reference to the One Data Share authentication token to use
     * @param ods_url borrowed reference to the url that One Data Share is running on
     * @param rest_caller moved pointer to the object to use for making REST API calls
     */
    Transfer_service_impl(const std::string& ods_auth_token,
                          const std::string& ods_url,
                          std::unique_ptr<Rest> rest_caller);

    /**
     * Makes a REST API call to transfer the specified resources to the specified location.
     *
     * @param source borrowed reference to the source of the transfer
     * @param destination borrowed reference to the destination of the transfer
     * @param options borrowed reference to the the options to use for this transfer request
     *
     * @return the id of the new transfer job
     *
     * @exception Connection_error if unable to connect to One Data Share
     * @exception Unexpected_response_error if an unexpected response is received from One Data Share
     */
    std::string transfer(const Source& source,
                         const Destination& destination,
                         const Transfer_options& options) const override;

    // TODO: implement
    std::unique_ptr<Transfer_status> status(const std::string& id) const override;

private:
    /** Url to the One Data Share server to make REST API calls to. */
    const std::string ods_url_;

    /** Pointer to the object used to make REST API calls. */
    const std::unique_ptr<Rest> rest_caller_;

    /** Headers used in REST API calls. */
    const std::unordered_multimap<std::string, std::string> headers_;
};

} // namespace Internal
} // namespace One_data_share

#endif // ONEDATASHARE_TRANSFER_SERVICE_IMPL_H
