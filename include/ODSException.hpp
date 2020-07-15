/**
 * ODSException.hpp
 * Andrew Mikalsen
 * 7/15/20
 */

#ifndef ODS_EXCEPTION_HPP_INCLUDED
#define ODS_EXCEPTION_HPP_INCLUDED

#include <stdexcept>

namespace ods {
    /**
     * General exception for exceptions thrown by One Data Share.
     */
    class ODSException : public std::runtime_error {
        public:
            ODSException(const std::string& what_arg);
            ODSException(const char* what_arg);
            virtual ~ODSException();
    };

    /**
     * Exception thrown when unable to connect to One Data Share.
     */
    class ODSConnectionException : public ODSException {
        public:
            ODSConnectionException(const std::string& what_arg);
            ODSConnectionException(const char* what_arg);
            virtual ~ODSConnectionException();
    };
}

#endif // ODS_EXCEPTION_HPP_INCLUDED