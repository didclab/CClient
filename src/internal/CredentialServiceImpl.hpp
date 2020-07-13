/*
 * CredentialServiceImpl.hpp
 * Andrew Mikalsen
 * 7/9/20
 */

#include <memory>
#include <CredentialService.hpp>
#include <Rest.hpp>

namespace ods {
    namespace internal {
        /**
         * Service that makes REST API calls to One Data Share related to
         * registering credentials.
         */
        class CredentialServiceImpl: public CredentialService {
            public:
                /**
                 * Creates a new CredentialServiceImpl object with the specified
                 * token, url, and rest caller.
                 * 
                 * @param ods_auth_token borrowed reference to the token to use
                 * for REST API calls
                 * @param ods_url borrowed reference to the url to make REST API
                 * calls to
                 * @param rest_caller object to use for making REST API calls
                 */
                CredentialServiceImpl(const std::string& ods_auth_token, const std::string& ods_url, std::unique_ptr<rest::Rest> rest_caller);
                virtual std::string oauth_url(OAuthEndpointType type) const override;
                virtual bool register_credential(CredentialEndpointType type, const std::string& cred_id, const std::string& uri, const std::string& username, const std::string& secret) const override;
                virtual std::vector<std::string> credential_id_list(EndpointType type) const override;
                virtual ~CredentialServiceImpl() override;
            private:
                /**
                 * One Data Share authentication token used in REST API calls.
                 */
                const std::string _ods_auth_token;

                /**
                 * Url to the One Data Share server to make REST API calls to.
                 */
                const std::string _ods_url;

                /**
                 * Pointer to the object used to make REST API calls.
                 */
                const std::unique_ptr<rest::Rest> _rest_caller;
        };
    }
}