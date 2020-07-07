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
#include <Resource.hpp>

namespace ods {
    /**
     * Service providing access to an endpoint of a specific type and credential id. Endpoint objects cannot be copied
     * via their copy constructor nor their copy assignment operator.
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

            /**
             * Gets the Resource found using the specified identifier. The
             * specifics of the identifier are dependent on the endpoint type.
             * For endpoints that look up resources by paths, the identifier
             * will be the path from the root of the endpoint to the resource.
             * For endpoints that look up resoruces by id, the identifier will
             * be the id of the resource to look up. Endpoint types that use
             * paths are Dropbox, SFTP, FTP, S3, GFTP, and GTTP. Endpoint types
             * that use ids are Google Drive and Box.
             * 
             * @param identifier string used to tell the endpoint how to find
             * the resource
             */
            virtual Resource list(std::string identifier) = 0;

            Endpoint(const Endpoint&) = delete;
            Endpoint& operator=(const Endpoint&) = delete;

            virtual ~Endpoint() = 0;
        protected:
            Endpoint() = default;
    };
}

#endif // ENDPOINT_HPP_INCLUDED