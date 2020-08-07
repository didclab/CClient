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
 * General exception thrown due to an error related to communicating with One Data Share.
 */
class Ods_error : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

/**
 * Exception thrown when a connection-related error occurs.
 */
class Connection_error : public Ods_error {
public:
    using Ods_error::Ods_error;
};

/**
 * Exception thrown when an unexpected response is received from One Data Share.
 */
class Unexpected_response_error : public Ods_error {
public:
    /**
     * Creates a new Unexpeected_response_error with the specified message and status code.
     *
     * @param what_arg borrowed reference to the error message
     * @param status status code from the unexpected response
     */
    Unexpected_response_error(const std::string& what_arg, int status);

    /**
     * The status code of the unexpected response.
     */
    const int status;
};

} // namespace One_data_share

#endif // ONEDATASHARE_ODS_ERROR_H