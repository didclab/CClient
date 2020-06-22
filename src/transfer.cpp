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
}