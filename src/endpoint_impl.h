/**
 * @file endpoint_impl.h
 * Defines the internal implementation of classes needed to interact with an endpoint's file sytem.
 *
 * @author Andrew Mikalsen
 * @date 7/20/20
 */

#ifndef ONEDATASHARE_ENDPOINT_IMPL_H
#define ONEDATASHARE_ENDPOINT_IMPL_H

#include <memory>
#include <string>
#include <unordered_map>

#include <onedatashare/endpoint.h>
#include <onedatashare/endpoint_type.h>

#include "rest.h"

namespace Onedatashare {
namespace Internal {

/**
 * Service that makes REST API calls to OneDataShare related to an endpoint's file system.
 */
class Endpoint_impl : public Endpoint {
public:
    /**
     * Creates a new Endpoint_impl object for the specified endpoint with the specified connection to OneDataShare
     * using the specified rest caller.
     *
     * @param type the type of endpoint to return
     * @param cred_id borrowed reference to the credential id of the endpoint to use
     * @param ods_auth_token borrowed reference to the OneDataShare authentication token to use
     * @param ods_url borrowed reference to the url that OneDataShare is running on
     * @param rest_caller moved pointer to the object to use for making REST API calls
     */
    Endpoint_impl(Endpoint_type type,
                  const std::string& cred_id,
                  const std::string& ods_auth_token,
                  const std::string& ods_url,
                  std::unique_ptr<Rest> rest_caller);

    /**
     * Makes a REST API call to create the Resource object corresponding to the specified resource.
     *
     * @param identifier borrowed reference to the path or id, dependending on the endpoint type, that the endpoint
     * needs in order to locate the resource
     *
     * @return the created Resource
     *
     * @exception Connection_error if unable to connect to OneDataShare
     * @exception Unexpected_response_error if an unexpected response is received from OneDataShare
     */
    Resource list(const std::string& identifier) const override;

    /**
     * Makes a REST API call to remove the specified resource.
     *
     * @param identifier borrowed reference to the path or id, depending on the endpoint type, that the endpoint
     * needs in order to locate the directory containing the resource to remove
     * @param to_delete borrowed reference to the name or id, depending on the endpoint type, that the endpoint
     * needs in order to locate the resource to remove from within the specified directory
     *
     * @exception Connection_error if unable to connect to OneDataShare
     * @exception Unexpected_response_error if an unexpected response is received from OneDataShare
     */
    void remove(const std::string& identifier, const std::string& to_delete) const override;

    /**
     * Makes a REST API call to create a directory with the specified name.
     *
     * @param identifier borrowed reference to the path or id, depending on the endpoint type, that the endpoint
     * needs in order to locate the directory to create the new directory under
     * @param folder_to_create borrowed reference to the name of the directory to create
     *
     * @exception Connection_error if unable to connect to OneDataShare
     * @exception Unexpected_response_error if an unexpected response is received from OneDataShare
     */
    void mkdir(const std::string& identifier, const std::string& folder_to_create) const override;

    /**
     * Makes a REST API call to download the specified file.
     *
     * @param identifier borrowed reference to the path or id, depending on the endpoint type, that the endpoint
     * needs in order to locate the directory containing the resource to download
     * @param file_to_download borrowed reference to the name or id depending on the endpoint type, that the
     * endpoint needs in order to locate the file to download from within the specified directory
     *
     * @exception Connection_error if unable to connect to OneDataShare
     * @exception Unexpected_response_error if an unexpected response is received from OneDataShare
     */
    void download(const std::string& identifier, const std::string& file_to_download) const override;

private:
    /** Type of the endpoint used in REST API calls. */
    const Endpoint_type type_;

    /** Credential id of the endpoint used in REST API calls. */
    const std::string cred_id_;

    /** Url to the OneDataShare server to make REST API calls to. */
    const std::string ods_url_;

    /** Pointer to the object used to make REST API calls. */
    const std::unique_ptr<Rest> rest_caller_;

    /** Headers used in REST API calls. */
    const std::unordered_multimap<std::string, std::string> headers_;
};

} // namespace Internal
} // namespace Onedatashare

#endif // ONEDATASHARE_ENDPOINT_IMPL_H
