/*
 * Item.cpp
 * Andrew Mikalsen
 * 6/24/20
 */

#include <Item.hpp>

namespace ods {
    // TODO: implement Item
    std::string Item::path() const {
        return _path;
    }

    std::string Item::id() const {
        return _id;
    }

    long Item::size() const {
        return _size;
    }
}