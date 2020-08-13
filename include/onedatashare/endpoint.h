/**
 * @file endpoint.h
 * Defines structs and classes needed to interact with an endpoint's file system.
 *
 * @author Andrew Mikalsen
 * @date 6/29/20
 */

#ifndef ONEDATASHARE_ENDPOINT_H
#define ONEDATASHARE_ENDPOINT_H

#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "endpoint_type.h"

namespace Onedatashare {

/**
 * Represents a directory, file, or link, otherwise refered to as a resource, from an endpoint's file system.
 */
struct Resource {
    /** Id of the resource if the resource has an id, no value otherwise. */
    std::optional<std::string> id;

    /** Name of the resource. */
    std::string name;

    /** Size of the resource in bytes. */
    long size;

    /** Time the resource was created. */
    long time;

    /** If the resource is a directory. */
    bool is_directory;

    /** If the resource is a file. */
    bool is_file;

    /** Symbolic link of the resource if the resource is a symbolic link, no value otherwise. */
    std::optional<std::string> link;

    /** Permissions of the resource if the resource has permissions, no value otherwise. */
    std::optional<std::string> permissions;

    /** List of the resources contained by this resource if this resource can contain other resources, no value
     * otherwise. A resource that containes no resources will have an empty list which distinguishes it from a resource
     * that cannot contain resources. */
    std::optional<std::vector<Resource>> contained_resources;
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
     * communicating with One Data Share at the specified url, passing ownership of the Endpoint object to the
     * caller. It is expected that the specified authentication token is valid, that the specified credential id is
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
     * Creates a Resource object corresponding to the resource found at the specified location. The Resource is
     * guaranteed to have an id defined if and only if created by an endpoint that supports ids. If the Resource is a
     * directory, then the Resource is guaranteed to have contained resources, though directories contained by the
     * Resource will not have contained resources. It is expected that the authentication token used to create this
     * Endpoint object is valid, that a connection can be made to One Data Share, that a connection can be made from One
     * Data Share to the endpoint specified by the credential id, and that the specified resource exists at the
     * specified location. If these preconditions are not met, exceptions may be thrown.
     *
     * @param identifier borrowed reference to the path or id, dependending on the endpoint type, that the endpoint
     * needs in order to locate the resource
     *
     * @return the created Resource
     *
     * @exception Connection_error if unable to connect to One Data Share
     * @exception Unexpected_response_error if an unexpected response is received from One Data Share
     *
     * @see Endpoint_type
     */
    virtual Resource list(const std::string& identifier) const = 0;

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

} // namespace Onedatashare

#endif // ONEDATASHARE_ENDPOINT_H
