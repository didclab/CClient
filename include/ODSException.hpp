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

    /**
     * Exception thrown when an unexpected internal server error is received
     * from One Data Share.
     */
    class ODSInternalServerException : public ODSException {
        public:
            ODSInternalServerException(const std::string& what_arg);
            ODSInternalServerException(const char* what_arg);
            virtual ~ODSInternalServerException();
    };

    /**
     * Exception thrown then an unexpected response is received from One Data
     * Share.
     */
    class ODSUnexpectedResponseException : public ODSException {
        public:
            ODSUnexpectedResponseException(const std::string& what_arg, const std::string& body, int status);
            ODSUnexpectedResponseException(const char* what_arg, const std::string& body, int status);

            /**
             * Gets a reference to the body of the unexpected response. The 
             * returned reference lives only as long as the object itself.
             * 
             * @return a temporary reference to the unexpected response's body
             */
            const std::string& body() const;

            /**
             * Gets the status of the unexpected response.
             * 
             * @return the unexpected response's status code
             */
            int status() const;

            virtual ~ODSUnexpectedResponseException();
        private:
            const std::string _body;
            const int _status;
    };
}

#endif // ODS_EXCEPTION_HPP_INCLUDED