/*
 * OneDataShareException.hpp
 * Andrew Mikalsen
 * 7/16/20
 */

#ifndef ONE_DATA_SHARE_EXCEPTION_HPP_INCLUDED
#define ONE_DATA_SHARE_EXCEPTION_HPP_INCLUDED

#include <stdexcept>

namespace ods {
    /**
     * General exception thrown by One Data Share.
     */
    class OneDataShareException : public std::runtime_error {
        public:
            OneDataShareException(const std::string& what_arg);
            OneDataShareException(const char* what_arg);
            virtual ~OneDataShareException();
    };
}

#endif // ONE_DATA_SHARE_EXCEPTION_HPP_INCLUDED