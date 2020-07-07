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
     * Service providing access to an endpoint of a specific type and credential
     * id. Endpoint objects cannot be copied via their copy constructor nor
     * their copy assignment operator.
     * 
     * <p>
     * Different endpoint types may have slightly different behavior
     * and functionality. These differences are described as follows.
     * </p>
     * 
     * <dl>
     * <dt>Dropbox</dt>
     * <dd>Uses names and paths to identify resources.</dd>
     * 
     * <dt>Google Drive</dt>
     * <dd>Uses ids to identify resources.</dd>
     * 
     * <dt>SFTP</dt>
     * <dd>Uses names and paths to identify resources.</dd>
     * 
     * <dt>FTP</dt>
     * <dd>Uses names and paths to identify resources.</dd>
     * 
     * <dt>Box</dt>
     * <dd>Uses ids to identify resources.</dd>
     * 
     * <dt>S3</dt>
     * <dd>Uses names and paths to identify resources.</dd>
     * 
     * <dt>GFTP</dt>
     * <dd>Uses names and paths to identify resources.</dd>
     * 
     * <dt>HTTP</dt>
     * <dd>Uses names and paths to identify resources.</dd>
     * </dl>
     */
    class Endpoint {
        public:
            /**
             * Creates a new Endpoint object of the specified type with the
             * specifed credential id and authentication token, passing
             * ownership of the Endpoint object to the caller.
             * 
             * @param type borrowed reference to the type of endpoint to return
             * @param cred_id borrowed reference to the credential id of the
             * endpoint to use
             * @param ods_auth_token borrowed reference to the One Data Share
             * authentication token to use
             * 
             * @return a unique pointer to a new Endpoint object
             */
            static std::unique_ptr<Endpoint> create(const EndpointType& type, const std::string& cred_id, const std::string& ods_auth_token);

            /**
             * Creates a Resource object corresponding to the resource found at
             * the specified location if the endpoint could find the resource.
             * The user is expected to check for a null pointer unless they are
             * absolutely certain that the resource was found. Ownership of the
             * returned Resource object is passed to the caller.
             * 
             * @param identifier borrowed reference to the path or id,
             * dependending on the endpoint type, that the endpoint needs in
             * order to locate the resource
             * 
             * @return a unique pointer to the created Resource or a null
             * pointer if no resource was found
             */
            virtual std::unique_ptr<Resource> list(const std::string& identifier) const = 0;

            /**
             * Removes the specified resource from the endpoint if the resource
             * was found.
             * 
             * @param identifier borrowed reference to the path or id, depending
             * on the endpoint type, that the endpoint needs in order to locate
             * the directory containing the resource to remove
             * @param to_delete borrowed reference to the name or id, depending
             * on the endpoint type, that the endpoint needs in order to locate
             * the resource to remove from within the specified directory
             * 
             * @return true if and only if this operation successfully removed
             * the specified resource from the endpoint
             */
            virtual bool remove(const std::string& identifier, const std::string& to_delete) const = 0;

            /**
             * Creates a new directory with the specified name under the
             * specified directory. The specified directory must exist. If the
             * specified resource is not a directory, false is returned.
             * 
             * @param identifier borrowed reference to the path or id, depending
             * on the endpoint type, that the endpoint needs in order to locate
             * the directory to create the new directory under
             * @param folder_to_create borrowed reference to the name of the
             * directory to create
             * 
             * @return true if and only if this operation successfully created
             * the the new directory under the specified directory
             */
            virtual bool mkdir(const std::string& identifier, const std::string& folder_to_create) const = 0;

            /**
             * Downloads the specified resource if the resource was found.
             * 
             * @param identifier borrowed reference to the path or id, depending
             * on the endpoint type, that the endpoint needs in order to locate
             * the directory containing the resource to download
             * @param file_to_download borrowed reference to the name or id,
             * depending on the endpoint type, that the endpoint needs in order
             * to locate the resource to download from within the specified
             * directory
             * 
             * @return true if and only if this operation successfully
             * downloaded the specified resource from the endpoint
             */
            virtual bool download(const std::string& identifier, const std::string& file_to_download) const = 0;

            Endpoint(const Endpoint&) = delete;
            Endpoint& operator=(const Endpoint&) = delete;

            virtual ~Endpoint() = 0;
        protected:
            Endpoint() = default;
    };
}

#endif // ENDPOINT_HPP_INCLUDED