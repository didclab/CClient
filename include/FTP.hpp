/*
 * FTP.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef FTP_INCLUDED
#define FTP_INCLUDED

#include <AccountEndpointCredential.hpp>
#include <Endpoint.hpp>

namespace ods {
    class FTP: public Endpoint {
        public:
            FTP(const std::string ods_auth_token);
            void add(const AccountEndpointCredential cred) const;
            virtual Item resolve() const override;
            virtual Item resolve(const std::string path) const override;
            virtual ~FTP() override = default;
    };
}

#endif // FTP_INCLUDED