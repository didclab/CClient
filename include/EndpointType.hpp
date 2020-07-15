/*
 * EndpointType.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef ENDPOINT_TYPE_HPP_INCLUDED
#define ENDPOINT_TYPE_HPP_INCLUDED

namespace ods {
    /**
     * Contains the possible types of an endpoint.
     */
    enum class EndpointType {
        DROPBOX, GOOGLE_DRIVE, SFTP, FTP, BOX, S3, GFTP, HTTP
    };
}

#endif // ENDPOINT_TYPE_HPP_INCLUDED