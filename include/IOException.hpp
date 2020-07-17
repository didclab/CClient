/*
 * IOException.hpp
 * Andrew Mikalsen
 * 7/15/20
 */

#ifndef IO_EXCEPTION_HPP_INCLUDED
#define IO_EXCEPTION_HPP_INCLUDED

#include <stdexcept>

namespace ods {
    /**
     * Exception thrown when an I/O operation fails.
     */
    class IOException : public std::runtime_error {
        public:
            IOException(const std::string& what_arg);
            IOException(const char* what_arg);
            virtual ~IOException();
    };
}

#endif // IO_EXCEPTION_HPP_INCLUDED