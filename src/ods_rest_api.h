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

/** Path of the REST API call for listing a resource on a Box endpoint. */
constexpr auto box_ls_path {"api/box/ls"};

/** Path of the REST API call for listing a resource on a Dropbox endpoint. */
constexpr auto dropbox_ls_path {"/api/dropbox/ls"};

/** Path of the REST API call for listing a resource on an FTP endpoint. */
constexpr auto ftp_ls_path {"/api/ftp/ls"};

/** Path of the REST API call for listing a resource on a Google Drive endpoint. */
constexpr auto google_drive_ls_path {"/api/googledrive/ls"};

/** Path of the REST API call for listing a resource on a GFTP endpoint. */
constexpr auto gftp_ls_path {"/api/gsiftp/ls"};

/** Path of the REST API call for listing a resource on an HTTP endpoint. */
constexpr auto http_ls_path {"/api/http/ls"};

/** Path of the REST API call for listing a resource on an S3 endpoint. */
constexpr auto s3_ls_path {"/api/s3/ls"};

/** Path of the REST API call for listing a resource on an SFTP endpoint. */
constexpr auto sftp_ls_path {"/api/sftp/ls"};

/** Path of the REST API call for removing a file from a Box endpoint. */
constexpr auto box_rm_path {"api/box/rm"};

/** Path of the REST API call for removing a file from a Dropbox endpoint. */
constexpr auto dropbox_rm_path {"/api/dropbox/rm"};

/** Path of the REST API call for removing a file from an FTP endpoint. */
constexpr auto ftp_rm_path {"/api/ftp/rm"};

/** Path of the REST API call for removing a file from a Google Drive endpoint. */
constexpr auto google_drive_rm_path {"/api/googledrive/rm"};

/** Path of the REST API call for removing a file from a GFTP endpoint. */
constexpr auto gftp_rm_path {"/api/gsiftp/rm"};

/** Path of the REST API call for removing a file from an HTTP endpoint. */
constexpr auto http_rm_path {"/api/http/rm"};

/** Path of the REST API call for removing a file from an S3 endpoint. */
constexpr auto s3_rm_path {"/api/s3/rm"};

/** Path of the REST API call for removing a file from an SFTP endpoint. */
constexpr auto sftp_rm_path {"/api/sftp/rm"};

/** Path of the REST API call for making a directory on a Box endpoint. */
constexpr auto box_mkdir_path {"api/box/mkdir"};

/** Path of the REST API call for making a directory on a Dropbox endpoint. */
constexpr auto dropbox_mkdir_path {"/api/dropbox/mkdir"};

/** Path of the REST API call for making a directory on an FTP endpoint. */
constexpr auto ftp_mkdir_path {"/api/ftp/mkdir"};

/** Path of the REST API call for making a directory on a Google Drive endpoint. */
constexpr auto google_drive_mkdir_path {"/api/googledrive/mkdir"};

/** Path of the REST API call for making a directory on a GFTP endpoint. */
constexpr auto gftp_mkdir_path {"/api/gsiftp/mkdir"};

/** Path of the REST API call for making a directory on an HTTP endpoint. */
constexpr auto http_mkdir_path {"/api/http/mkdir"};

/** Path of the REST API call for making a directory on an S3 endpoint. */
constexpr auto s3_mkdir_path {"/api/s3/mkdir"};

/** Path of the REST API call for making a directory on an SFTP endpoint. */
constexpr auto sftp_mkdir_path {"/api/sftp/mkdir"};

/** Path of the REST API call for downloading a file from a Box endpoint. */
constexpr auto box_download_path {"api/box/download"};

/** Path of the REST API call for downloading a file from a Dropbox endpoint. */
constexpr auto dropbox_download_path {"/api/dropbox/download"};

/** Path of the REST API call for downloading a file from an FTP endpoint. */
constexpr auto ftp_download_path {"/api/ftp/download"};

/** Path of the REST API call for downloading a file from a Google Drive endpoint. */
constexpr auto google_drive_download_path {"/api/googledrive/download"};

/** Path of the REST API call for downloading a file from a GFTP endpoint. */
constexpr auto gftp_download_path {"/api/gsiftp/download"};

/** Path of the REST API call for downloading a file from an HTTP endpoint. */
constexpr auto http_download_path {"/api/http/download"};

/** Path of the REST API call for downloading a file from an S3 endpoint. */
constexpr auto s3_download_path {"/api/s3/download"};

/** Path of the REST API call for downloading a file from an SFTP endpoint. */
constexpr auto sftp_download_path {"/api/sftp/download"};

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
