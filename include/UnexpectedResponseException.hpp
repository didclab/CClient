/*
 * UnexpectedResponseException.hpp
 * Andrew Mikalsen
 * 7/15/20
 */

#include <stdexcept>

namespace ods {
    /**
     * Exception thrown when an unexpected response is received.
     */
    class UnexpectedResponseException : std::runtime_error {
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