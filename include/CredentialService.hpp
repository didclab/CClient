/*
 * CredentialService.hpp
 * Andrew Mikalsen
 * 7/7/20
 */

#ifndef CREDENTIAL_SERVICE_HPP_INCLUDED
#define CREDENTIAL_SERVICE_HPP_INCLUDED

namespace ods {
    /**
     * Service providing all functionality related to registering credentials
     * with One Data Share.
     */
    class CredentialService {
        public:
            CredentialService(const CredentialService&) = delete;
            CredentialService& operator=(const CredentialService&) = delete;

            virtual ~CredentialService() = 0;
        private:
            CredentialService() = default;
    };
}

#endif // CREDENTIAL_SERVICE_HPP_INCLUDED