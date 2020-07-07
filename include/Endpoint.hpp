/*
 * Endpoint.hpp
 * Andrew Mikalsen
 * 6/29/20
 */

#ifndef ENDPOINT_HPP_INCLUDED
#define ENDPOINT_HPP_INCLUDED

#include <memory>
#include <string>
#include <EndpointType.hpp>

namespace ods {
    /**
     * Service providing access to an endpoint of a specific type and credential id.
     */
    class Endpoint {
        public:
            /**
             * Creates a new Endpoint object of the specified type with the specifed credential id and authentication
             * token, passing ownership to the caller.
             * 
             * @param type the type of endpoint to return
             * @param cred_id the credential id of the endpoint to use
             * @param ods_auth_token the one data share authentication token to use
             * 
             * @return a unique pointer to a new Endpoint object
             */
            static std::unique_ptr<Endpoint> create(EndpointType type, std::string cred_id, std::string ods_auth_token);

            Endpoint(const Endpoint&) = delete;
            Endpoint& operator=(const Endpoint&) = delete;
            
            virtual ~Endpoint() = 0;
        protected:
            Endpoint() = default;
    };
}

#endif // ENDPOINT_HPP_INCLUDED