/*
 * endpoint_type.h
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef ONEDATASHARE_ENDPOINT_TYPE_H
#define ONEDATASHARE_ENDPOINT_TYPE_H

namespace One_data_share {

/**
 * Contains the possible endpoint types that can be used for making transfers and interacting with an endpoint's file
 * system. Note that different endpoint types may differ slightly in behavior and functionality as described by
 * each enumeration.
 */
enum class Endpoint_type {
    /** Indicates a Dropbox endpoint. Dropbox endpoints use names and paths to identify resources. */
    dropbox,
    /** Indicates a Google Drive endpoint. Google Drive endpoints use ids to identify resources. */
    google_drive,
    /** Indicates an SFTP endpoint. SFTP endpoints use names and paths to identify resources. */
    sftp,
    /** Indicates an FTP endpoint. FTP endpoints use names and paths to identify resources. */
    ftp,
    /** Indicates a Box endpoint. Box endpoints use ids to identify resources. */
    box,
    /** Indicates an S3 endpoint. S3 endpoints use names and paths to identify resources. */
    s3,
    /** Indicates a Grid FTP endpoint. FTP endpoints use names and paths to identify resources. */
    gftp,
    /** Indicates an HTTP endpoint. HTTP endpoints use names and paths to identify resources. */
    http
};

} // namespace One_data_share

#endif // ONEDATASHARE_ENDPOINT_TYPE_H