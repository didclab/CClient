/*
 * Transfer.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef TRANSFER_HPP_INCLUDED
#define TRANSFER_HPP_INCLUDED

#include <OneDataShare.hpp>
#include <TransferStatus.hpp>
#include <TransferRequest.hpp>

namespace ods {
    class Transfer: public OneDataShare {
        public:
            Transfer(const std::string ods_auth_token);
            std::string transfer(const TransferRequest& request) const;
            TransferStatus get_transfer_status(const std::string& id) const;
            virtual ~Transfer() override = default;
    };
}

#endif // TRANSFER_HPP_INCLUDED