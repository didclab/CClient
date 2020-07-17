/*
 * ods_error.h
 * Andrew Mikalsen
 * 7/16/20
 */

#ifndef ONEDATASHARE_ODS_ERROR_H
#define ONEDATASHARE_ODS_ERROR_H

#include <stdexcept>

namespace One_data_share {
    /**
     * General exception thrown by One Data Share.
     */
    class Ods_error : public std::runtime_error {
    public:
        Ods_error(const std::string& what_arg);
        Ods_error(const char* what_arg);
        virtual ~Ods_error();
    };

    /**
     * Exception thrown when an I/O operation fails.
     */
    class IO_error : public Ods_error {
    public:
        IO_error(const std::string& what_arg);
        IO_error(const char* what_arg);
        virtual ~IO_error();
    };

    /**
     * Exception thrown when an unexpected response is received.
     */
    class Unexpected_response_error : public Ods_error {
    public:
        Unexpected_response_error(const std::string& what_arg, int status);
        Unexpected_response_error(const char* what_arg, int status);

        virtual ~Unexpected_response_error();

        /**
         * The status code of the unexpected response.
         */
        const int status;
    };
}

#endif // ONEDATASHARE_ODS_ERROR_H