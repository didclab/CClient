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
                                                   std::string cred_id,
                                                   std::string directory_identifier);

        virtual ~Destination() = 0;

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
         * @param cred_id the credential identifier of the endpoint to
         * transfer from
         * @param directory_identifier the path or id, depending on the endpoint type, that is needed in order to locate
         * the directory containing the resources to transfer
         * @param resource_identifiers the names or ids, depending on the endpoint type, that are needed in order to
         * locate the resources to transfer from within the specified directory
         *
         * @return a unique pointer to a new Source object
         */
        static std::unique_ptr<Source> create(Endpoint_type type,
                                              std::string cred_id,
                                              std::string directory_identifier,
                                              std::vector<std::string> resource_identifiers);

        virtual ~Source() = 0;

    protected:
        Source();
    };

    // TODO: define
    class Transfer_options {
    public:
        virtual ~Transfer_options() = 0;
    };

    // TODO: define
    class Transfer_status {
    public:
        virtual ~Transfer_status() = 0;
    };

    /**
     * Service providing all functionality related to making transfers.
     */
    class Transfer_service {
    public:
        /**
         * Creates a new Transfer_service object with the specified authentication token, passing ownership of the
         * Transfer_service object to the caller.
         *
         * @param ods_auth_token the One Data Share authentication token to use
         *
         * @return a unique pointer to a new Transfer_service object
         */
        static std::unique_ptr<Transfer_service> create(std::string ods_auth_token);

        virtual ~Transfer_service() = 0;

        Transfer_service(const Transfer_service&) = delete;

        Transfer_service& operator=(const Transfer_service&) = delete;

        /**
         * Starts a new transfer job from the specified source to the specified destination with the specified options.
         *
         * @param source borrowed reference to the source of the transfer
         * @param destination borrowed reference to the destination of the transfer
         * @param options borrowed reference to the the options to use for this transfer request
         *
         * @return the id of the new transfer job
         */
        virtual std::string transfer(const Source& source,
                                     const Destination& destination,
                                     const Transfer_options& options) const = 0;

        /**
         * Checks the status of the specified transfer job by creatinh a new Transfer_status object whose ownership is
         * passed to the caller.
         *
         * @param id borrowed reference to the id of the transfer job to check
         *
         * @return unique pointer to the status of the transfer job
         */
        virtual std::unique_ptr<Transfer_status> status(const std::string& id) const = 0;

    protected:
        Transfer_service();
    };
}

#endif // ONEDATASHARE_TRANSFER_SERVICE_H