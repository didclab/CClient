/*
 * HTTP.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef HTTP_HPP_INCLUDED
#define HTTP_HPP_INCLUDED

#include <Endpoint.hpp>

namespace ods {
    class HTTP: public Endpoint {
        public:
            HTTP(const std::string ods_auth_token);
            virtual Item resolve() const override;
            virtual Item resolve(const std::string path) const override;
            virtual ~HTTP() override = default;
    };
}

#endif // HTTP_HPP_INCLUDED