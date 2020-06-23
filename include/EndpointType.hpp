/*
 * EndpointType.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef ENDPOINT_TYPE_HPP_INCLUDED
#define ENDPOINT_TYPE_HPP_INCLUDED

namespace ods {
    enum class EndpointType {
        DROPBOX, GOOGLE_DRIVE, SFTP, FTP, BOX, GFTP, HTTP
    };
}

#endif // ENDPOINT_HPP_TYPE_INCLUDED