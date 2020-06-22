/*
 * one_data_share.cpp
 * Andrew Mikalsen
 * 6/22/20
 * 
 * Contains implementations from one_data_share.hpp that aren't significant enough to warrant their own file.
 */

#include <string>
#include <one_data_share.hpp>

namespace ods {
    OneDataShare::OneDataShare(const std::string ods_auth_token) : _ods_auth_token(ods_auth_token) { 
    }
}