/** 
 * @file transfer_service.h
 * Defines structs and classes needed to perform and observe transfer operations.
 *
 * @author Andrew Mikalsen
 * @date 7/7/20
 */

#ifndef ONEDATASHARE_TRANSFER_SERVICE_H
#define ONEDATASHARE_TRANSFER_SERVICE_H

#include <memory>
#include <string>
#include <vector>

#include "endpoint_type.h"

namespace One_data_share {

/**
 * Indicates the destination endpoint of a transfer. Different endpoint types may differ slightly in behavior and
 * functionality as described in {@link Endpoint_type}.
 */
struct Destination {
    /** Endpoint type to transfer to. */
    Endpoint_type type;

    /** Credential identifier of the endpoint to transfer to. */
    std::string cred_id;

    /** Path or id, depending on the endpoint type, used to locate the directory to place transfered resources. */
    std::string directory_identifier;
};

/**
 * Indicates the source endpoint of a transfer. Different endpoint types may differ slightly in behavior and
 * functionality as described in {@link Endpoint_type}.
 */
struct Source {
    /** Endpoint type to transfer from. */
    Endpoint_type type;

    /** Credential identifier of the endpoint to transfer from. */
    std::string cred_id;

    /** Path or id, depending on the endpoint type, used to locate the directory to transfer from. */
    std::string directory_identifier;

    /** Names or ids, depending on the endpoint type, used to locate the resources to transfer from within the source
     * directory. */
    std::vector<std::string> resource_identifiers;
};

/**
 * Options to use in a transfer request.
 */
struct Transfer_options {
    // TODO: define
};

/**
 * Status of a submitted transfer job.
 */
class Transfer_status {
    // TODO: define
public:
    /// @private
    virtual ~Transfer_status() = 0;

protected:
    /// @private
    Transfer_status();
};

/**
 * Service providing all functionality related to making transfers.
 */
class Transfer_service {
public:
    /**
     * Creates a new Transfer_service object with the specified authentication token, passing ownership of the
     * Transfer_service object to the caller. It is expected that the specified authentication token is valid.
     *
     * @param ods_auth_token borrowed reference to the One Data Share authentication token to use
     *
     * @return a unique pointer to a new Transfer_service object
     */
    static std::unique_ptr<Transfer_service> create(const std::string& ods_auth_token);

    /**
     * Creates a new Transfer_service object with the specified authentication token communicating with One Data Share
     * at the specified url, passing ownership of the Transfer_service object to the caller. It is expected that the
     * specified authentication token is valid and that One Data Share is running at the specified url.
     *
     * @param ods_auth_token borrowed reference to the One Data Share authentication token to use
     * @param url borrowed reference to the url that One Data Share is running on
     *
     * @return a unique pointer to a new Transfer_service object
     */
    static std::unique_ptr<Transfer_service> create(const std::string& ods_auth_token, const std::string& url);

    /// @private
    virtual ~Transfer_service() = 0;

    /// @private
    Transfer_service(const Transfer_service&) = delete;

    /// @private
    Transfer_service& operator=(const Transfer_service&) = delete;

    /// @private
    Transfer_service(Transfer_service&&) = delete;

    /// @private
    Transfer_service& operator=(Transfer_service&&) = delete;

    /**
     * Starts a new transfer job from the specified source to the specified destination with the specified options.
     * It is expected that the authentication token used to create this Transfer_service object is valid, that a
     * connection can be made to One Data Share, that a connection can be made to the source endpoint, that a
     * connection can be made to the second endpoint, that the resources on the source endpoint can be found at the
     * specified locations, that the directory on the destination endpoint can be found at the specified location, and
     * that One Data Share is able to read and write as neceessary. If these preconditions are not met, exceptions may
     * be thrown.
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
    virtual std::string transfer(const Source& source,
                                 const Destination& destination,
                                 const Transfer_options& options) const = 0;

    /**
     * Checks the status of the specified transfer job by creating a new Transfer_status object whose ownership is
     * passed to the caller. It is expected that the authentication token used to create this Transfer_service
     * object is valid, that a connection can be made to One Data Share, and that the specified id is a valid job
     * id. If these preconditions are not met, exceptions may be thrown.
     *
     * @param id borrowed reference to the id of the transfer job to check
     *
     * @return unique pointer to the status of the transfer job
     *
     * @exception Connection_error if unable to connect to One Data Share
     * @exception Unexpected_response_error if an unexpected response is received from One Data Share
     */
    virtual std::unique_ptr<Transfer_status> status(const std::string& id) const = 0;

protected:
    /// @private
    Transfer_service();
};

} // namespace One_data_share

#endif // ONEDATASHARE_TRANSFER_SERVICE_H
