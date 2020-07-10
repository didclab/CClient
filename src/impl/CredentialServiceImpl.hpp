/*
 * CredentialServiceImpl.hpp
 * Andrew Mikalsen
 * 7/9/20
 */

#include <CredentialService.hpp>

namespace ods {
    namespace impl {
        /**
         * Service that makes REST API calls to One Data Share related to
         * registering credentials.
         */
        class CredentialServiceImpl: public CredentialService {
            public:
                /**
                 * Creates a new CredentialServiceImpl object with the specified
                 * One Data Share authentication token.
                 */
                CredentialServiceImpl(std::string ods_auth_token);
                virtual std::string oauth_url(const OAuthEndpointType type) const override;
                virtual bool register_credential(const CredentialEndpointType type, const std::string& cred_id, const std::string& uri, const std::string& username, const std::string& secret) const override;
                virtual std::vector<std::string> credential_id_list(const EndpointType type) const override;
                virtual ~CredentialServiceImpl() override = default;
        };
    }
}