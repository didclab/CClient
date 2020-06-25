/*
 * Source.hpp
 * Andrew Mikalsen
 * 6/23/20
 */

#ifndef SOURCE_HPP_INCLUDED
#define SOURCE_HPP_INCLUDED

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
            std::unordered_set<ItemInfo, ItemInfo::Hash> info_list() const;
        private:
            const EndpointType _type;
            const std::string _cred_id;
            const std::optional<ItemInfo> _info;
            const std::optional<std::unordered_set<ItemInfo, ItemInfo::Hash>> _info_list;
            std::unordered_set<ItemInfo, ItemInfo::Hash> create_info_set(std::vector<Item> items) const;
    };
}

#endif // SOURCE_HPP_INCLUDED