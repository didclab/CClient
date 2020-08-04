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
    /// @private
    Ods_error(const std::string& what_arg);

    /// @private
    Ods_error(const char* what_arg);

    /// @private
    virtual ~Ods_error() = default;
};

/**
 * Exception thrown when a connection-related error occurs.
 */
class Connection_error : public Ods_error {
public:
    /// @private
    Connection_error(const std::string& what_arg);

    /// @private
    Connection_error(const char* what_arg);

    /// @private
    virtual ~Connection_error() = default;
};

/**
 * Exception thrown when an unexpected response is received from One Data Share.
 */
class Unexpected_response_error : public Ods_error {
public:
    /// @private
    Unexpected_response_error(const std::string& what_arg, int status);

    /// @private
    Unexpected_response_error(const char* what_arg, int status);

    /// @private
    virtual ~Unexpected_response_error() = default;

    /**
     * The status code of the unexpected response.
     */
    const int status;
};

} // namespace One_data_share

#endif // ONEDATASHARE_ODS_ERROR_H