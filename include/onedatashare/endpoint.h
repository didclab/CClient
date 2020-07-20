/*
 * endpoint.h
 * Andrew Mikalsen
 * 6/29/20
 */

#ifndef ONEDATASHARE_ENDPOINT_H
#define ONEDATASHARE_ENDPOINT_H

#include <memory>
#include <string>
#include <vector>

#include "endpoint_type.h"

namespace One_data_share {

    /**
     * Represents a resource from an endpoint's file system containing a directory, file, or link.
     */
    class Resource {
    public:
        virtual ~Resource() = 0;

        Resource(const Resource&) = delete;

        Resource& operator=(const Resource&) = delete;

        Resource(Resource&&) = default;

        Resource& operator=(Resource&&) = default;

        /**
         * Gets the id of the Resource if the Resource has an id. The Resource will have an id if and only if the
         * endpoint used supports ids. The caller is expected to check for a null pointer if they are not certain that
         * the Resource has an id. The returned pointer is reference counted, so the pointer is safe to use even after
         * the Resource is deallocated.
         *
         * @return a shared pointer to the id of the Resource or a null pointer if the Resource doesn't have an id
         */
        virtual std::shared_ptr<const std::string> id() const = 0;

        /**
         * Gets the name of the Resource.
         *
         * @return a copy of the name of the Resource
         */
        virtual std::string name() const = 0;

        /**
         * Gets the size of the Resource. If size is called on a Resource without a size, 0 is returned.
         *
         * @return a copy of the size of the Resource
         */
        virtual long size() const = 0;

        /**
         * Gets the time of the Resource.
         *
         * @return a copy of the time of the Resource
         */
        virtual long time() const = 0;

        /**
         * Determines whether or not the Resource is a directory.
         *
         * @return true if and only if the Resource is a directory.
         */
        virtual bool is_directory() const = 0;

        /**
         * Determines whether or not the Resource is a file.
         *
         * @return true if and only if the Resource is a file.
         */
        virtual bool is_file() const = 0;

        /**
         * Gets the link of the Resource if and only if the Resource is a link. The caller is expected to check for a
         * null pointer unless they are absolutely certain that the Resource is a link. The returned pointer is
         * reference counted, so the pointer is safe to use even after the Resource is deallocated.
         *
         * @return a shared pointer to the link of the Resource or a null pointer if the Resource isn't a link
         */
        virtual std::shared_ptr<const std::string> link() const = 0;

        /**
         * Gets the permissions of the Resource if the resource has permissions. The caller is expected to check for a
         * null pointer unless they are absolutely certain the Resource has permissions. The returned pointer is
         * reference counted, so the pointer is safe to use even after the Resource is deallocated.
         *
         * @return a shared pointer to the permissions of the Resource or a null pointer if the Resource isn't a link
         */
        virtual std::shared_ptr<const std::string> permissions() const = 0;

        /**
         * Gets the Resource objects contained in this Resource if and only if this Resource is a directory. The caller
         * is expected to check for a null pointer unless they are absolutely certain the Resource is a directory or
         * they already checked via is_directory. The returned pointer is reference counted, so the pointer is safe to
         * use even after the Resource is deallocated.
         *
         * @return a shared pointer to a vector holding the Resource objects contained in this Resource or null if the
         * Resource isn't a directory
         */
        virtual std::shared_ptr<const std::vector<std::shared_ptr<const Resource>>> contained_resources() const = 0;

    protected:
        Resource();
    };

    /**
     * Service providing access to an endpoint of a specific type and credential id.
     *
     * <p>
     * Different endpoint types may differ slightly in behavior and functionality. These differences are described
     * as follows.
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
         * Creates a new Endpoint object of the specified type with the specifed credential id and authentication token,
         * passing ownership of the Endpoint object to the caller.
         *
         * @param type the type of endpoint to return
         * @param cred_id borrowed reference to the credential id of the endpoint to use
         * @param ods_auth_token borrowed reference to the One Data Share authentication token to use
         *
         * @return a unique pointer to a new Endpoint object
         */
        static std::unique_ptr<Endpoint> create(Endpoint_type type,
                                                const std::string& cred_id,
                                                const std::string& ods_auth_token);

        virtual ~Endpoint() = 0;

        Endpoint(const Endpoint&) = delete;

        Endpoint& operator=(const Endpoint&) = delete;

        Endpoint(Endpoint&&) = default;

        Endpoint& operator=(Endpoint&&) = default;

        /**
         * Creates a Resource object corresponding to the resource found at the specified location if the endpoint could
         * find the resource. The user is expected to check for a null pointer unless they are absolutely certain that
         * the resource was found. Ownership of the returned Resource object is passed to the caller.
         *
         * @param identifier borrowed reference to the path or id, dependending on the endpoint type, that the endpoint
         * needs in order to locate the resource
         *
         * @return a unique pointer to the created Resource or a null pointer if no resource was found
         */
        virtual std::unique_ptr<Resource> list(const std::string& identifier) const = 0;

        /**
         * Removes the specified resource from the endpoint if the resource was found.
         *
         * @param identifier borrowed reference to the path or id, depending on the endpoint type, that the endpoint
         * needs in order to locate the directory containing the resource to remove
         * @param to_delete borrowed reference to the name or id, depending on the endpoint type, that the endpoint
         * needs in order to locate the resource to remove from within the specified directory
         *
         * @return true if and only if this operation successfully removed the specified resource from the endpoint
         */
        virtual bool remove(const std::string& identifier, const std::string& to_delete) const = 0;

        /**
         * Creates a new directory with the specified name under the specified directory. The specified directory must
         * exist. If the specified resource is not a directory, false is returned.
         *
         * @param identifier borrowed reference to the path or id, depending on the endpoint type, that the endpoint
         * needs in order to locate the directory to create the new directory under
         * @param folder_to_create borrowed reference to the name of the directory to create
         *
         * @return true if and only if this operation successfully created the the new directory under the specified
         * directory
         */
        virtual bool mkdir(const std::string& identifier, const std::string& folder_to_create) const = 0;

        /**
         * Downloads the specified resource if the resource was found.
         *
         * @param identifier borrowed reference to the path or id, depending on the endpoint type, that the endpoint
         * needs in order to locate the directory containing the resource to download
         * @param file_to_download borrowed reference to the name or id depending on the endpoint type, that the
         * endpoint needs in order to locate the resource to download from within the specified directory
         *
         * @return true if and only if this operation successfully downloaded the specified resource from the endpoint
         */
        virtual bool download(const std::string& identifier, const std::string& file_to_download) const = 0;

    protected:
        Endpoint();
    };
}

#endif // ONEDATASHARE_ENDPOINT_H