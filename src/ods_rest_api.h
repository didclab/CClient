/**
 * @file ods_rest_api.h
 * Defines constants related to the specification of the One Data Share REST API.
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

/** Path of the REST API call for making transfers. */
constexpr auto transfer_job_path {"/api/transfer-job"};

/** Parameter of the GET ls api call indicating the credential id. */
constexpr auto get_ls_cred_id_param {"credId"};

/** Parameter of the GET ls api call indicating the path to the target resource. */
constexpr auto get_ls_path_param {"path"};

/** Parameter of the GET ls api call indicating the id of the target resource. */
constexpr auto get_ls_identifier_param {"identifier"};

/** Parameter or JSON object field value indicating a box endpoint. */
constexpr auto box_type {"box"};

/** Parameter or JSON object field value indicating a dropbox endpoint. */
constexpr auto dropbox_type {"dropbox"};

/** Parameter or JSON object field value indicating an ftp endpoint. */
constexpr auto ftp_type {"ftp"};

/** Parameter or JSON object field value indicating a gftp endpoint. */
constexpr auto gftp_type {"gftp"};

/** Parameter or JSON object field value indicating a google drive endpoint. */
constexpr auto google_drive_type {"gdrive"};

/** Parameter or JSON object field value indicating an http endpoint. */
constexpr auto http_type {"http"};

/** Parameter or JSON object field value indicating an s3 endpoint. */
constexpr auto s3_type {"s3"};

/** Parameter or JSON object field value indicating an sftp endpoint. */
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

/** Field of Stat json object indicating the id. */
constexpr auto stat_id {"id"};

/** Field of Stat json object indicating the name. */
constexpr auto stat_name {"name"};

/** Field of Stat json object indicating the size. */
constexpr auto stat_size {"size"};

/** Field of Stat json object indicating time created. */
constexpr auto stat_time {"time"};

/** Field of Stat json object indicating if the Stat is a directory. */
constexpr auto stat_dir {"dir"};

/** Field of Stat json object indicating if the stat is a file. */
constexpr auto stat_file {"file"};

/** Field of Stat json object indicating the symbolic link. */
constexpr auto stat_link {"link"};

/** Field of Stat json object indicating the permissions. */
constexpr auto stat_permissions {"permissions"};

/** Field of Stat json object indicating an array of nested Stat objects. */
constexpr auto stat_files {"files"};

/** Field of DeleteOperation json object indicating the credential id of the target endpoint. */
constexpr auto delete_operation_cred_id {"credId"};

/** Field of DeleteOperation json object indicating the path to the target directory. */
constexpr auto delete_operation_path {"path"};

/** Field of DeleteOperation json object indicating the id of the target directory. */
constexpr auto delete_operation_id {"id"};

/** Field of DeleteOperation json object indicating the identifier of the target resource. */
constexpr auto delete_operation_to_delete {"toDelete"};

/** Field of MkdirOperation json object indicating the credential id of the target endpoint. */
constexpr auto mkdir_operation_cred_id {"credId"};

/** Field of MkdirOperation json object indicating the path to the target directory. */
constexpr auto mkdir_operation_path {"path"};

/** Field of MkdirOperation json object indicating the id of the target directory. */
constexpr auto mkdir_operation_id {"id"};

/** Field of MkdirOperation json object indicating the new directory name. */
constexpr auto mkdir_operation_folder_to_create {"folderToCreate"};

/** Field of DownloadOperation json object indicating the credential id of the target endpoint. */
constexpr auto download_operation_cred_id {"credId"};

/** Field of DownloadOperation json object indicating the path to the target directory. */
constexpr auto download_operation_path {"path"};

/** Field of DownloadOperation json object indicating the id of the target directory. */
constexpr auto download_operation_id {"id"};

/** Field of DownloadOperation json object indicating the target file. */
constexpr auto download_operation_file_to_download {"fileToDownload"};

/** Field of EntityInfo json object indicating resource id. */
constexpr auto entity_info_id {"id"};

/** Field of EntityInfo json object indicating resource path. */
constexpr auto entity_info_path {"path"};

/** Field of Source json object indicating endpoint type. */
constexpr auto source_type {"type"};

/** Field of Source json object indicating credential id. */
constexpr auto source_cred_id {"credId"};

/** Field of Source json object indicating target directory. */
constexpr auto source_info {"info"};

/** Field of Source json object indicating target resources. */
constexpr auto source_info_list {"infoList"};

/** Field of Destination json object indicating endpoint type. */
constexpr auto destination_type {"type"};

/** Field of Destination json object indicating credential id. */
constexpr auto destination_cred_id {"credId"};

/** Field of Destination json object indicating target directory. */
constexpr auto destination_info {"info"};

/** Field of TransferJob json object indicating source of transfer. */
constexpr auto transfer_job_request_source {"source"};

/** Field of TransferJob json object indicating destination of transfer. */
constexpr auto transfer_job_request_destination {"destination"};

} // namespace Api
} // namespace Internal
} // namespace One_data_share

#endif // ONEDATASHARE_ODS_REST_API_H
