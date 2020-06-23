/*
 * Transfer.cpp
 * Andrew Mikalsen
 * 6/23/20
 */

#include <Transfer.hpp>

namespace ods {
    Transfer::Transfer(const std::string ods_auth_token) : OneDataShare(ods_auth_token) {
    }

    std::string Transfer::transfer(const TransferRequest& request) const {
        // TODO: implement
    }

    TransferStatus get_transfer_status(const std::string& id) const {
        // TODO: implement
    }
}