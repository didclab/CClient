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

namespace ods {
    class TransferService{
        public:
            static std::unique_ptr<TransferService> create(std::string ods_auth_token);

            virtual std::string transfer(Source source, Destination destination, TransferOptions options) = 0;

            virtual ~TransferService() = 0;
        protected:
            TransferService() = default;
    };
}

#endif // TRANSFER_SERVICE_HPP_INCLUDED