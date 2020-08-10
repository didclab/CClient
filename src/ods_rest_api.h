/**
 * @file ods_rest_api.h
 * Defines constants and functions related to the specification of the One Data Share REST API.
 *
 * @author Andrew Mikalsen
 * @date 8/10/20
 */

#ifndef ONEDATASHARE_ODS_REST_API_H
#define ONEDATASHARE_ODS_REST_API_H

namespace One_data_share {
namespace Internal {
namespace Api {

/** Path of the REST API call for oauth. */
constexpr auto oauth_path {"/api/oauth"};

/** Path of the REST API call for credentials. */
constexpr auto cred_path {"/api/cred"};

/** Parameter value indicating a box endpoint. */
constexpr auto box_type {"box"};

/** Parameter value indicating a dropbox endpoint. */
constexpr auto dropbox_type {"dropbox"};

/** Parameter value indicating an ftp endpoint. */
constexpr auto ftp_type {"ftp"};

/** Parameter value indicating a gftp endpoint. */
constexpr auto gftp_type {"gftp"};

/** Parameter value indicating a google drive endpoint. */
constexpr auto google_drive_type {"gdrive"};

/** Parameter value indicating an http endpoint. */
constexpr auto http_type {"http"};

/** Parameter value indicating an s3 endpoint. */
constexpr auto s3_type {"s3"};

/** Parameter value indicating an sftp endpoint. */
constexpr auto sftp_type {"sftp"};

/** Field of EndpointCrededential json object indicating credential id. */
constexpr auto endpoint_credential_account_id {"accountId"};

/** Field of EndpointCrededential json object indicating uri. */
constexpr auto endpoint_credential_uri {"uri"};

/** Field of EndpointCrededential json object indicating username. */
constexpr auto endpoint_credential_username {"username"};

/** Field of EndpointCrededential json object indicating password. */
constexpr auto endpoint_credential_secret {"secret"};

/** Field of CredList json object indicating array of credential ids. */
constexpr auto cred_list_credential_list {"credentialList"};

} // namespace Api
} // namespace Internal
} // namespace One_data_share

#endif // ONEDATASHARE_ODS_REST_API_H
