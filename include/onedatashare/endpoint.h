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
    /// @private
    virtual ~Resource() = 0;

    /// @private
    Resource(const Resource&) = delete;

    /// @private
    Resource& operator=(const Resource&) = delete;

    /// @private
    Resource(Resource&&) = delete;

    /// @private
    Resource& operator=(Resource&&) = delete;

    /**
     * Gets the id of the Resource if the Resource has an id. The Resource will have an id if and only if the
     * endpoint type used supports ids. The caller is expected to check for a null pointer if they are not certain that
     * the Resource has an id. The returned pointer is reference counted, so the pointer is safe to use even after
     * the Resource is deallocated.
     *
     * @return a shared pointer to the id of the Resource or a null pointer if the Resource doesn't have an id
     *
     * @see Endpoint_type
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
     * Gets the Resource objects contained in this Resource if and only if this Resource is a directory and this
     * resource was returned from the list method of an Endpoint object. The caller is expected to check for a null
     * pointer unless they are absolutely certain the Resource has contained resources. The returned pointer is
     * reference counted, so the pointer is safe to use even after the Resource is deallocated.
     *
     * @return a shared pointer to a vector holding the Resource objects contained in this Resource or null if the
     * Resource isn't a directory
     */
    virtual std::shared_ptr<const std::vector<std::shared_ptr<const Resource>>> contained_resources() const = 0;

protected:
    /// @private
    Resource();
};

/**
 * Service providing access to an endpoint of a specific type and credential id. Different endpoint types may differ
 * slightly in behavior and functionality as described in {@link Endpoint_type}.
 */
class Endpoint {
public:
    /**
     * Creates a new Endpoint object of the specified type with the specifed credential id and authentication token,
     * passing ownership of the Endpoint object to the caller. It is expected that the specified authentication
     * token is valid and that the specified credential id is registered with One Data Share.
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

    /**
     * Creates a new Endpoint object of the specified type with the specifed credential id and authentication token
     * communicating with One Data Share at the specified url, passing ownership of the Endpoint object to the caller.
     * It is expected that the specified authentication token is valid, that the specified credential id is
     * registered with One Data Share, and that One Data Share is running on the specified url.
     *
     * @param type the type of endpoint to return
     * @param cred_id borrowed reference to the credential id of the endpoint to use
     * @param ods_auth_token borrowed reference to the One Data Share authentication token to use
     * @param url borrowed reference to the url that One Data Share is running on
     *
     * @return a unique pointer to a new Endpoint object
     */
    static std::unique_ptr<Endpoint> create(Endpoint_type type,
                                            const std::string& cred_id,
                                            const std::string& ods_auth_token,
                                            const std::string& url);

    /// @private
    virtual ~Endpoint() = 0;

    /// @private
    Endpoint(const Endpoint&) = delete;

    /// @private
    Endpoint& operator=(const Endpoint&) = delete;

    /// @private
    Endpoint(Endpoint&&) = delete;

    /// @private
    Endpoint& operator=(Endpoint&&) = delete;

    /**
     * Creates a Resource object corresponding to the resource found at the specified location. Ownership of the
     * returned Resource object is passed to the caller. It is expected that the authentication token used to create
     * this Endpoint object is valid, that a connection can be made to One Data Share, that a connection can be made
     * from One Data Share to the endpoint specified by the credential id, and that the specified resource exists at
     * the specified location. If these preconditions are not met, exceptions may be thrown.
     *
     * @param identifier borrowed reference to the path or id, dependending on the endpoint type, that the endpoint
     * needs in order to locate the resource
     *
     * @return a unique pointer to the created Resource
     *
     * @exception Connection_error if unable to connect to One Data Share
     * @exception Unexpected_response_error if an unexpected response is received from One Data Share
     *
     * @see Endpoint_type
     */
    virtual std::unique_ptr<Resource> list(const std::string& identifier) const = 0;

    /**
     * Removes the specified resource from the endpoint. It is expected that the authentication token used to create
     * this Endpoint object is valid, that a connection can be made to One Data Share, that a connection can be made
     * from One Data Share to the endpoint specified by the credential id, that the specified resource exists at
     * the specified location, and that One Data Share is able to remove the specified resource. If these
     * preconditions are not met, exceptions may be thrown.
     *
     * @param identifier borrowed reference to the path or id, depending on the endpoint type, that the endpoint
     * needs in order to locate the directory containing the resource to remove
     * @param to_delete borrowed reference to the name or id, depending on the endpoint type, that the endpoint
     * needs in order to locate the resource to remove from within the specified directory
     *
     * @exception Connection_error if unable to connect to One Data Share
     * @exception Unexpected_response_error if an unexpected response is received from One Data Share
     *
     * @see Endpoint_type
     */
    virtual void remove(const std::string& identifier, const std::string& to_delete) const = 0;

    /**
     * Creates a new directory with the specified name under the specified directory. It is expected that the
     * authentication token used to create this Endpoint object is valid, that a conenction can be made to One Data
     * Share, that a connection can be made from One Data Share to the endpoint specified by the credential id,
     * that the specified resource both is a directory and exists at the specified location, and that One Data Share
     * is able to create a directory under the specified directory. If these preconditions are not met, exceptions
     * may be thrown.
     *
     * @param identifier borrowed reference to the path or id, depending on the endpoint type, that the endpoint
     * needs in order to locate the directory to create the new directory under
     * @param folder_to_create borrowed reference to the name of the directory to create
     *
     * @exception Connection_error if unable to connect to One Data Share
     * @exception Unexpected_response_error if an unexpected response is received from One Data Share
     *
     * @see Endpoint_type
     */
    virtual void mkdir(const std::string& identifier, const std::string& folder_to_create) const = 0;

    /**
     * Downloads the specified file. It is expected that the authentication token used to create this Endpoint
     * object is valid, that a conenction can be made to One Data Share, that a connection can be made from One Data
     * Share to the endpoint specified by the credential id, that the specified resource exists at the specified
     * location, and that the specified resource is a file. If these preconditions are not met, exceptions may be
     * thrown.
     *
     * @param identifier borrowed reference to the path or id, depending on the endpoint type, that the endpoint
     * needs in order to locate the directory containing the resource to download
     * @param file_to_download borrowed reference to the name or id depending on the endpoint type, that the
     * endpoint needs in order to locate the file to download from within the specified directory
     *
     * @exception Connection_error if unable to connect to One Data Share
     * @exception Unexpected_response_error if an unexpected response is received from One Data Share
     *
     * @see Endpoint_type
     */
    virtual void download(const std::string& identifier, const std::string& file_to_download) const = 0;

protected:
    /// @private
    Endpoint();
};

} // namespace One_data_share

#endif // ONEDATASHARE_ENDPOINT_H