/*
 * SFTP.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef SFTP_HPP_INCLUDED
#define SFTP_HPP_INCLUDED

#include <AccountEndpointCredential.hpp>
#include <Endpoint.hpp>

namespace ods {
    class SFTP: public Endpoint {
        public:
            SFTP(const std::string ods_auth_token);
            void add(const AccountEndpointCredential cred) const;
            virtual Item resolve() const override;
            virtual Item resolve(const std::string path) const override;
            virtual ~SFTP() override = default;
    };
}

#endif // SFTP_HPP_INCLUDED