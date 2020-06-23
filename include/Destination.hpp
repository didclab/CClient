/*
 * Destination.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef DESTINATION_INCLUDED
#define DESTINATION_INCLUDED

#include <string>
#include <EndpointType.hpp>
#include <Item.hpp>
#include <ItemInfo.hpp>

namespace ods {
    class Destination {
        public:
            Destination(const EndpointType type, const std::string cred_id, const Item& item);
            EndpointType type() const;
            std::string cred_id() const;
            ItemInfo info() const;
        private:
            const EndpointType _type;
            const std::string _cred_id;
            const ItemInfo _info;
    };
}

#endif // DESTINATION_INCLUDED