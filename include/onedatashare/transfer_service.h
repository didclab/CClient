/*
 * transfer_service.h
 * Andrew Mikalsen
 * 7/7/20
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
class Destination {
public:
    /**
     * Creates a new Destination object with the specified endpoint and directory.
     *
     * @param type the endpoint type to transfer to
     * @param cred_id the credential identifier of the endpoint to transfer to
     * @param directory_identifier  the path or id, depending on the endpoint type, that is needed in order to
     * locate the directory in which the transfered resources should be placed
     *
     * @see Endpoint_type
     */
    Destination(Endpoint_type type, const std::string& cred_id, const std::string& directory_identifier);

    /** Type of the destinatin endpoint. */
    Endpoint_type type;

    /** Credential identifier of the destination endpoint. */
    std::string cred_id;

    /** Identifier of the destination directory. */
    std::string directory_identifier;
};

/**
 * Indicates the source endpoint of a transfer. Different endpoint types may differ slightly in behavior and
 * functionality as described in {@link Endpoint_type}.
 */
class Source {
public:
    /**
     * Creates a new Source object with the specified endpoint and resources.
     *
     * @param type the endpoint type to transfer from
     * @param cred_id borrowed reference to the credential identifier of the endpoint to transfer from
     * @param directory_identifier borrowed reference to the path or id, depending on the endpoint type, that is
     * needed in order to locate the directory containing the resources to transfer
     * @param resource_identifiers borrowed reference to the names or ids, depending on the endpoint type, that are
     * needed in order to locate the resources to transfer from within the specified directory
     *
     * @see Endpoint_type
     */
    Source(Endpoint_type type,
           const std::string& cred_id,
           const std::string& directory_identifier,
           const std::vector<std::string>& resource_identifiers);

    /** Type of the source endpoint. */
    Endpoint_type type;

    /** Credential identifier of the source endpoint. */
    std::string cred_id;

    /** Identifier of the source directory. */
    std::string directory_identifier;

    /** Identifiers of resources to transfer from the source endpoint. */
    std::vector<std::string> resource_identifiers;
};

/**
 * Options to use in a transfer request.
 */
class Transfer_options {
    // TODO: define
public:
    /**
     * Creates a new Transfer_options object.
     */
    Transfer_options();
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