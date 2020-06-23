/*
 * Box.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef BOX_HPP_INCLUDED
#define BOX_HPP_INCLUDED

#include <Endpoint.hpp>

namespace ods {
    class Box: public Endpoint {
        public:
            Box(const std::string ods_auth_token);
            void add() const;
            virtual Item resolve() const override;
            virtual Item resolve(const std::string path) const override;
            virtual ~Box() override = default;
    };
}

#endif // BOX_HPP_INCLUDED
