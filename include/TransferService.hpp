/*
 * TransferService.hpp
 * Andrew Mikalsen
 * 7/7/20
 */

#ifndef TRANSFER_SERVICE_HPP_INCLUDED
#define TRANSFER_SERVICE_HPP_INCLUDED

#include <memory>
#include <string>
#include <Destination.hpp>
#include <Source.hpp>
#include <TransferOptions.hpp>
#include <TransferStatus.hpp>

namespace ods {
    /**
     * Service providing all functionality related to making transfers.
     */
    class TransferService{
        public:
            /**
             * Creates a new TransferService object with the specified
             * authentication token, passing ownership of the TransferService
             * object to the caller.
             * 
             * @param ods_auth_token the one data share authentication token to
             * use
             * 
             * @return a unique pointer to a new TransferService object
             */
            static std::unique_ptr<TransferService> create(std::string ods_auth_token);

            /**
             * Starts a new transfer job from the specified source to the
             * specified destination with the specified options.
             * 
             * @param source borrowed pointer to the source of the transfer
             * @param destination borrowed pointer to the destination of the
             * transfer
             * @param options borrowed pointer to the the options to use for
             * this transfer request
             * 
             * @return the id of the new transfer job
             */
            virtual std::string transfer(Source* source, Destination* destination, TransferOptions* options) const = 0;

            /**
             * Checks the status of the specified transfer job
             * 
             * @param id the id of the transfer job to check
             * 
             * @return the status of the transfer job
             */
            virtual TransferStatus status(std::string id) const = 0;

            TransferService(const TransferService&) = delete;
            TransferService& operator=(const TransferService&) = delete;

            virtual ~TransferService() = 0;
        protected:
            TransferService() = default;
    };
}

#endif // TRANSFER_SERVICE_HPP_INCLUDED