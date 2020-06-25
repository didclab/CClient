/*
 * Source.cpp
 * Andrew Mikalsen
 * 6/23/20
 */

#include <Source.hpp>

namespace ods {
    // TODO: implement Source

    Source::Source(const EndpointType type, const std::string cred_id, const std::vector<Item> items) :
        _type(type),
        _cred_id(cred_id),
        _info_list(create_info_set(items)) {
    }

    EndpointType Source::type() const {
        return _type;
    }

    std::string Source::cred_id() const {
        return _cred_id;
    }

    ItemInfo Source::info() const {
        return _info.value();
    }

    std::unordered_set<ItemInfo, ItemInfo::Hash> Source::info_list() const {
        return _info_list.value();
    }

    std::unordered_set<ItemInfo, ItemInfo::Hash> Source::create_info_set(std::vector<Item> items) const {
        std::unordered_set<ItemInfo, ItemInfo::Hash> set;
        for (const Item& i : items) {
            set.insert(ItemInfo(i.id(), i.path(), i.size()));
        }
        return set;
    }
}