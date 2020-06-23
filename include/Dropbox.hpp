/*
 * Dropbox.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef DROPBOX_HPP_INCLUDED
#define DROPBOX_HPP_INCLUDED

#include <Endpoint.hpp>

namespace ods {
    class Dropbox: public Endpoint {
        public:
            Dropbox(const std::string ods_auth_token);
            void add() const;
            virtual Item resolve() const override;
            virtual Item resolve(const std::string path) const override;
            virtual ~Dropbox() override = default;
    };
}

#endif // DROPBOX_HPP_INCLUDED