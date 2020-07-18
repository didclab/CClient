/*
 * endpoint_type.h
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef ONEDATASHARE_ENDPOINT_TYPE_H
#define ONEDATASHARE_ENDPOINT_TYPE_H

namespace One_data_share {
    
    /**
     * Contains the possible types of an endpoint.
     */
    enum class Endpoint_type {
        dropbox,
        google_drive,
        sftp,
        ftp,
        box,
        s3,
        gftp,
        http
    };
}

#endif // ONEDATASHARE_ENDPOINT_TYPE_H