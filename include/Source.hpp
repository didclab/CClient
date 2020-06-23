/*
 * Source.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef SOURCE_HPP_INCLUDED
#define SOURCE_HPP_INCLUDED

#include <string>
#include <unordered_set>
#include <vector>
#include <EndpointType.hpp>
#include <Item.hpp>
#include <ItemInfo.hpp>

namespace ods {
    class Source {
        public:
            Source(const EndpointType type, const std::string cred_id, const std::vector<Item> items);
            Source(const EndpointType type, const std::string cred_id, const Item item);
            EndpointType type() const;
            std::string cred_id() const;
            ItemInfo info() const;
            std::unordered_set<ItemInfo> info_list() const;
        private:
            const EndpointType _type;
            const std::string _cred_id;
            const ItemInfo _info;
            const std::unordered_set<ItemInfo> _info_list;
    };
}

#endif // SOURCE_HPP_INCLUDED