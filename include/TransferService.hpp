/*
 * TransferService.hpp
 * Andrew Mikalsen
 * 7/7/20
 */

#ifndef TRANSFER_SERVICE_HPP_INCLUDED
#define TRANSFER_SERVICE_HPP_INCLUDED

#include <memory>
#include <string>

namespace ods {
    class TransferService{
        public:
            static std::unique_ptr<TransferService> create(std::string ods_auth_token);

            virtual ~TransferService() = 0;
        protected:
            TransferService() = default;
    };
}

#endif // TRANSFER_SERVICE_HPP_INCLUDED