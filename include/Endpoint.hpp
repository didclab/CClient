/*
 * Endpoint.hpp
 * Andrew Mikalsen
 * 6/23/30
 */

#ifndef ENDPOINT_INCLUDED
#define ENDPOINT_INCLUDED

#include <string>
#include <Item.hpp>
#include <OneDataShare.hpp>

namespace ods {
    class Endpoint: public OneDataShare {
        public:
            Endpoint(const std::string ods_auth_token);
            virtual Item resolve() const = 0;
            virtual Item resolve(const std::string path) const = 0;
    };
}

#endif // ENDPOINT_INCLUDED