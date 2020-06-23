/*
 * transfer.cpp
 * Andrew Mikalsen
 * 6/22/20
 * 
 * Contains implementations relating to transfers.
 */

#include <one_data_share.hpp>

namespace ods {
    Transfer::Transfer(const std::string ods_auth_token) : OneDataShare(ods_auth_token) {
    }

    std::string Transfer::transfer(const TransferRequest request) const {
        // TODO: impl
    }

    TransferStatus Transfer::get_transfer_status(const std::string id) const {
        // TODO: impl
    }

    TransferRequest::TransferRequest(const Source& source, const Destination& destination, const TransferOptions transfer_options, const int priority) :
        _source(source),
        _destination(destination),
        _options(transfer_options),
        _priority(priority) {
    }
}