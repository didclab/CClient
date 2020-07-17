/*
 * UnexpectedResponseException.hpp
 * Andrew Mikalsen
 * 7/15/20
 */

#ifndef UNEXPECTED_RESPONSE_EXCEPTION_HPP_INCLUDED
#define UNEXPECTED_RESPONSE_EXCEPTION_HPP_INCLUDED

#include "OneDataShareException.hpp"

namespace One_data_share {
    /**
     * Exception thrown when an unexpected response is received.
     */
    class UnexpectedResponseException : public OneDataShareException {
        public:
            UnexpectedResponseException(const std::string& what_arg, int status);
            UnexpectedResponseException(const char* what_arg, int status);

            /**
             * Gets the status code of the unexpected response.
             * 
             * @return the unexpected response's status code
             */
            int status() const;

            virtual ~UnexpectedResponseException();
        private:
            int _status;
    };
}

#endif // UNEXPECTED_RESPONSE_EXCEPTION_HPP_INCLUDED