/*
 * util.hpp
 * Andrew Mikalsen
 * 7/16/20
 */

#ifndef UTIL_HPP_INCLUDED
#define UTIL_HPP_INCLUDED

#include <string>

namespace ods {
    namespace util {

        constexpr auto ODS_URL = "https://onedatashare.org";

        /**
         * Sets the url in the config file to the specified string.
         * 
         * @param url mutably borrowed reference to the string to set the read
         * url to
         * 
         * @return true if and only if the config file was found and could be opened
         */
        bool load_url_from_config(std::string& url);
    }
}

#endif // UTIL_HPP_INCLUDED