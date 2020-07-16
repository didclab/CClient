/*
 * util.cpp
 * Andrew Mikalsen
 * 7/16/20
 */

#include <fstream>
#include "util.hpp"

namespace ods {
    namespace util {
        namespace {
            constexpr auto CONFIG_FILE_LOCATION = "token.txt";
        }

        bool load_url_from_config(std::string& url) {
            std::ifstream file(CONFIG_FILE_LOCATION);    
            if (!file.is_open()) {
                return false;
            }
            std::getline(file, url);

            file.close();
            return true;
        }
    }
}