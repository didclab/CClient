/*
 * S3.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef S3_INCLUDED
#define S3_INCLUDED

#include <AccountEndpointCredential.hpp>
#include <Endpoint.hpp>

namespace ods {
    class S3: public Endpoint {
        public:
            S3(const std::string ods_auth_token);
            void add(const AccountEndpointCredential cred) const;
            virtual Item resolve() const override;
            virtual Item resolve(const std::string path) const override;
            virtual ~S3() override = default;
    };
}

#endif // S3_INCLUDED