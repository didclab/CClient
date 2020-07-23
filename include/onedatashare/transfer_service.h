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
 * Indicates the destination endpoint of a transfer.
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
     * @return a unique pointer to the Destination object
     */
    static std::unique_ptr<Destination> create(Endpoint_type type,
                                               const std::string& cred_id,
                                               const std::string& directory_identifier);

    virtual ~Destination() = 0;

    Destination(const Destination&) = default;

    Destination& operator=(const Destination&) = default;

    Destination(Destination&&) = default;

    Destination& operator=(Destination&&) = default;

protected:
    Destination();
};

/**
 * Indicates the source endpoint of a transfer.
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
     * @return a unique pointer to a new Source object
     */
    static std::unique_ptr<Source> create(Endpoint_type type,
                                          const std::string& cred_id,
                                          const std::string& directory_identifier,
                                          const std::vector<std::string>& resource_identifiers);

    virtual ~Source() = 0;

    Source(const Source&) = default;

    Source& operator=(const Source&) = default;

    Source(Source&&) = default;

    Source& operator=(Source&&) = default;

protected:
    Source();
};

// TODO: define
class Transfer_options {
public:
    virtual ~Transfer_options() = 0;

protected:
    Transfer_options();
};

// TODO: define
class Transfer_status {
public:
    virtual ~Transfer_status() = 0;

protected:
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

    virtual ~Transfer_service() = 0;

    Transfer_service(const Transfer_service&) = delete;

    Transfer_service& operator=(const Transfer_service&) = delete;

    Transfer_service(Transfer_service&&) = default;

    Transfer_service& operator=(Transfer_service&&) = default;

    /**
     * Starts a new transfer job from the specified source to the specified destination with the specified options.
     * It is expected that the authentication token used to create this Transfer_service object is valid, that a
     * connection can be made to One Data Share, that a connection can be made to the source endpoint, that a
     * connection can be made to the second endpoint, that the resources on the source endpoint can be found at the
     * specified endpoint at the specified locatoin, that the directory on the destination endpoint can be found at
     * the specified location, and that One Data Share is able to write under the specified destination directory.
     * If these preconditions are not met, exceptions may be thrown.
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
    Transfer_service();
};

} // namespace One_data_share

#endif // ONEDATASHARE_TRANSFER_SERVICE_H