/*
 * CredentialServiceImpl.cpp
 * Andrew Mikalsen
 * 7/10/20
 */

#include "CredentialServiceImpl.hpp"

#include <utility>

namespace ods {
    namespace internal {
        CredentialServiceImpl::CredentialServiceImpl(const std::string& ods_auth_token, const std::string& ods_url, std::unique_ptr<rest::Rest> rest_caller) :
            _ods_auth_token(ods_auth_token),
            _ods_url(ods_url),
            _rest_caller(std::move(rest_caller)) {
        }
        CredentialServiceImpl::~CredentialServiceImpl() = default;
    }
}