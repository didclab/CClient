/*
 * AccountEndpointCredential.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef ACCOUNT_ENDPOINT_CREDENTIAL_HPP_INCLUDED
#define ACCOUNT_ENDPOINT_CREDENTIAL_HPP_INCLUDED

#include <string>

namespace ods {
    class AccountEndpointCredential {
        public:
            AccountEndpointCredential(const std::string account_id, const std::string uri, const std::string username, const std::string secret);
            AccountEndpointCredential(const AccountEndpointCredential&) = delete;
            AccountEndpointCredential& operator=(const AccountEndpointCredential&) = delete;
            std::string account_id() const;
            std::string uri() const;
            std::string username() const;
            std::string secret() const;
        private:
            const std::string _account_id;
            const std::string _uri;
            const std::string _username;
            const std::string _secret;
    };
}

#endif // ACCOUNT_ENDPOINT_CREDENTIAL_HPP_INCLUDED